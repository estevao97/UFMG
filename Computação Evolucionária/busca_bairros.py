import json
import math
import os

import requests
from bs4 import BeautifulSoup
from pyproj import Transformer

# Constants
URL_WIKIPEDIA = "https://pt.wikipedia.org/wiki/Lista_de_bairros_de_Belo_Horizonte"
URL_GEOCODER = "https://geocoder.pbh.gov.br/geocoder/v2/address?bairro={nome_bairro}"
HEADERS = {
    "User-Agent":
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
}
CACHE_FILE = "cache.json"


# Functions
def fetch_page(url):
    response = requests.get(url, headers=HEADERS)
    response.raise_for_status(
    )  # Raise an exception for 4xx or 5xx status codes.
    return response.content


def parse_neighborhoods_table(content):
    soup = BeautifulSoup(content, "html.parser")
    table = soup.find("table", {"class": "wikitable"})
    if not table:
        raise Exception("Table not found on the page.")

    neighborhoods_data = []
    for row in table.find_all("tr")[1:]:
        cols = row.find_all("td")
        if len(cols) >= 6:  # Ensure we have enough columns
            neighborhood_name = cols[3].get_text(
                strip=True).split("(")[0].strip()
            population = int(cols[4].get_text(strip=True).replace(u'\xa0', ""))
            area = float(cols[5].get_text().replace("\n",
                                                    "").replace(",", "."))
            neighborhoods_data.append({
                "name":
                neighborhood_name,
                "population":
                population,
                "area":
                area,
                "radius":
                math.sqrt(float(area) / math.pi)
            })
    return neighborhoods_data


def merge_duplicates(neighborhoods_data):
    i = 1
    while i < len(neighborhoods_data):
        curr_neighborhood = neighborhoods_data[i]
        last_neighborhood = neighborhoods_data[i - 1]

        if curr_neighborhood["name"] == last_neighborhood["name"]:
            population = curr_neighborhood["population"] + last_neighborhood[
                "population"]
            area = curr_neighborhood["area"] + last_neighborhood["area"]
            merged_neighborhood = {
                "name": curr_neighborhood["name"],
                "population": population,
                "area": area,
                "radius": math.sqrt(float(area) / math.pi)
            }

            neighborhoods_data[i - 1] = merged_neighborhood
            neighborhoods_data.pop(i)
        else:
            i += 1

    return neighborhoods_data


def fetch_geocode_data(neighborhood_name):
    cache = load_cache()
    if neighborhood_name in cache:
        return cache[neighborhood_name]

    url = URL_GEOCODER.format(nome_bairro=neighborhood_name)
    response = requests.get(url, headers=HEADERS)
    response.raise_for_status()
    data = response.json()
    cache[neighborhood_name] = data
    save_cache(cache)
    return data


def load_cache():
    if os.path.exists(CACHE_FILE):
        with open(CACHE_FILE, "r") as f:
            return json.load(f)
    return {}


def save_cache(cache):
    with open(CACHE_FILE, "w") as f:
        json.dump(cache, f)


def get_coordinates(geocode_data):
    address = geocode_data.get("endereco", [{}])[0]
    wkt = address.get('wkt')
    if wkt:
        coords = wkt.replace("POINT(", "").replace(")", "").split()
        return map(float, coords)
    return None


def main():
    try:
        page_content = fetch_page(URL_WIKIPEDIA)
        neighborhoods_data = parse_neighborhoods_table(page_content)
        neighborhoods_data = merge_duplicates(neighborhoods_data)
        print(len(neighborhoods_data))
        transformer = Transformer.from_crs("EPSG:31983", "EPSG:4326")

        counter = 0
        for neighborhood in neighborhoods_data:
            counter += 1
            try:
                print(
                    f"{counter} - Fetching data for neighborhood: {neighborhood['name']}"
                )
                geocode_data = fetch_geocode_data(neighborhood["name"])
                coords = get_coordinates(geocode_data)
                if coords:
                    x, y = coords
                    latitude, longitude = transformer.transform(x, y)
                    neighborhood["coordinates"] = f"{latitude}, {longitude}"
                else:
                    print(
                        f"No coordinates found for neighborhood: {neighborhood['name']}"
                    )
            except Exception as e:
                print(
                    f"Error processing neighborhood {neighborhood['name']}: {e}"
                )

        with open("bairros_bh_v2.json", "w", encoding="utf-8") as json_file:
            json.dump(neighborhoods_data,
                      json_file,
                      ensure_ascii=False,
                      indent=4)
        print("Data saved to bairros_bh_v2.json")

    except Exception as e:
        print(e)


# Execute main function
if __name__ == "__main__":
    main()

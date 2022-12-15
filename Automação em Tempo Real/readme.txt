TP - Automação em TempoReal

Introdução

A disciplina de Automação em Tempo Real tinha como objetivo proporcionar aos alunos um primeiro contato com os sistemas de tempo real,
ensinando desde os conceitos mais básicos que permeiam pelos sistemas de tempo real, até os inúmeros tipos de sistemas. No final da
disciplina foi proposto um trabalho prático final, com o objetivo de abordar os conceitos apreendidos durante a disciplina e validar 
o aprendizado. E esse repositório se refere a esse trabalho prático, desenvolvido por mim e pelo Daniel Benicá. A ideia proposta nesse
trabalho é simular o controle em tempo real de um banco de motores. Mais detalhes sobre a proposta do exercício pode ser encontrada no 
arquivo "Trabalho Final.pdf" presente na página da disciplina.

########################################################################################################################################

Pré Requesitos

Para que seja possível executar o programa no dispositivo, é necessário ter instalado alguma versão do compilador Python. Além dsso,
é necessário que o dispositivo tenha duas bibliotecas instaladas: a matplotlib num.py. Essas bibliotecas podem ser instaladas usando
o comando:

pip install -r requirements.txt

########################################################################################################################################

Instalação

O programa pode ser instalado no seu dispositivo baixando o código fonte ou fazendo um clone do repositório presente na página do GitHub
https://github.com/DanielBenica/TP_Automa-o_Tempo_Real

Para clonar o repositório do GitHub é necessário ter instalado no seu dispositivo o software Git e uma conta ativa no GitHub, 
https://github.com. Feito isso é necessário seguir os passos habituais para clonar um repositório.

    1- Abrir o terminal do git, ou qualquer outra ferramenta de desenvolvimento do Git, e logar com sua conta do GitHub
    2- Executar o comando git clone https://github.com/DanielBenica/TP_Automa-o_Tempo_Real.git

########################################################################################################################################

Execução

Para compilar o programa, é necessário entrar em sua pasta raiz e abrir o terminal. Feito isso é necessário executar o seguinte comando:

python_version main.py

em que se deve substituir python_version pela versão do compilador python de seu dispositivo. Exemplo:

python3 main.py

Para executar o synoptco é necessário executar o seguinte comando:

python3 synoptic.py

Feito isso é necessário imputar no terminal os Ids dos motores separados por espaço e em seguida
fornecer a referência de velocidade.

A porta utilizada para fazer conexão é a 51511.

########################################################################################################################################

Construído com

Esse projeto foi 100% construído usando a linguagem Python e usando paradgma de orientação a objetos.

########################################################################################################################################

Autores

Os autores desse projeto são:

Daniel Lourenço Zorzal Benicá - Documentação e desenvolvimento - https://www.linkedin.com/in/danielbenica/
Paulo Estêvão Nunes Santos - Documentação e desenvolvimento -  https://www.linkedin.com/in/paulo-estevao/

########################################################################################################################################
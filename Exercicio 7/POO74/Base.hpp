#ifndef BASE_HPP
#define BASE_HPP

class Base{
    
    int i;
    
    protected:
        int read() const { return i; }
        void set(int ii) { i = ii; }
    
    public:
        Base(int ii = 0) : i(ii) {}
        int value(int m) const { return m*i; }
};


class Derived : protected Base{
        
        int j;
        public:
            Derived(int jj = 0) : j(jj) {}
            void change(int x) { set(x); }
};


class Derived2 : public Derived{
        
        int j;
        public:
            Derived2(int kk = 0) : k(kk) {}
            void change(int y) { set(y); }
};

#endif

/*
1 - É possível adicionar uma função membro na classe Derived que chama a função read()? Sim, pois o modificador de acesso "protected" permite que os membros possam ser acessados por outras classes derivadas, neste caso Derived, e por classes "friend". E o uso do modificador de acesso "public" na herança mantém os níveis de acesso da classe basa.

2 - Alterando a herança para private, ainda assim é possível adicionar uma função membro na classe Derived que chama a função read()? Sim, pois o modificador de acesso "private" herda os membros public e protected da classe basa como privados para a classe derivada, não interferindo nos níveis de acesso, neste caso.

3 - É possível chamar a função read() a partir de um objeto do tipo Derived? Não, pois o modificador de acesso protected faz com que a função read() só possa ser acessada na própria classe, sendo necessário que um método público a chame para ser usada fora da classe. 

4 - Modifique o código de forma que a classe Derived use herança protected. Crie uma classe Derived2 que seja derivada da classe Derived utilizando herança public. É possível chamar read() a partir de uma função membro da classe Derived2? E o método value()? Sim, pois o modificador de acesso "protected" permite que os membros possam ser acessados por outras classes derivadas, neste caso Derived, e por classes "friend". E o uso do modificador de acesso "public" na herança mantém os níveis de acesso da classe basa.
*/
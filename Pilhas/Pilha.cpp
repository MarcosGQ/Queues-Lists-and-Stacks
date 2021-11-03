#include <iostream>

using namespace std;

// Declaração de classes
class Aluno;
class Stack;
class Node;

// Implementação de classes
class Aluno
{
	private:
		string nome;
		int mat;
		
	public:
		Aluno();
		~Aluno();
		void set_Nome(string nome);
		void set_Mat(int mat);
		string get_Nome();
		int get_Mat();	
};

class Stack
{
    private:
        Node* top; // guarda o endereço do nó que esta no topo
        int qtd;

    public:
        Stack();
        ~Stack();
        bool push(Aluno* obj);
        bool pop(Aluno* obj);
        bool show(Aluno* obj);
        bool isempty();
        int num_ele();
};

class Node
{
	friend Stack;
	
	private:
		Aluno D; // guarda o objeto
		 	
	public:
		Node* next; // guarda o endereço do proximo nó, que esta abaixo na pilha.
		Node();
		~Node();
		static Node* monta_no(Aluno* obj);
		static void desmonta_no(Node* p, Aluno* obj);	
};

//Implementação dos métodos da classe Aluno

Aluno::Aluno() 
{}

Aluno::~Aluno () 
{}

void Aluno::set_Nome (string nome)
{
	this->nome=nome; // usando "this" para não dar erro por trabalhar com variaveis de mesmo nome
}

void Aluno::set_Mat (int mat)
{
	this->mat=mat;
}

string Aluno::get_Nome ()
{
	return nome;
}

int Aluno::get_Mat ()
{
	return mat;
}

// Implementação dos métodos da classe Stack +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Stack::Stack ()
{
    top= 0; // inicialmente o topo não aponta para nada
    qtd= 0;
}

Stack::~Stack ()
{
    Node* p;
    while (top)
    {
        p= top;
        top= top->next; // top recebe o conteudo que esta em next, apontado por top.
        delete p;
    }
}

bool Stack::push (Aluno* obj)
{
    Node* p= Node::monta_no(obj); // cria-se um ponteiro de Node que receberá o endereço de p, criado no metodo monta_no. "p" aponta para o novo nó criado (new node).
    if (p)
    {
        p->next= top;
        top= p;
        qtd++;
        return true;
    }
    return false;
}

bool Stack::pop (Aluno* obj)
{
    if (!top) // 1º verifica se a pilha ta vazia
    {
        return 0;
    }
    Node* p= top; // 2º - cria-se um ponteiro que receberá o endereço do nó a ser removido
    top= top->next; // 3º - top aponta para o nó apontado por top, ou seja, top receberá o endereço do nó que vem depois desse a ser removido
    Node::desmonta_no (p, obj); // 4º - chama método para desmontar esse nó
	qtd--;
	return true; // 5º -  retorna true como um aviso de que tudo deu certo
}

bool Stack::show(Aluno* obj)
{
	if(!top)
	{
		return false;
	}	
	*obj= top->D;
	return true;
}

bool Stack::isempty()
{
	return !top;
}

int Stack::num_ele()
{
	return qtd;
}

// Implementação dos métodos da classe Node

Node::Node ()
{}

Node::~Node ()
{}

Node* Node::monta_no (Aluno* obj) // metodo que cria um novo nó
{
	Node* p= new Node; // 1º - cria-se um novo nó dinamico
	if (p) // 2º - verifica se foi criado o nó
	{
		p->D= *obj; // 3º - nó recebe o objeto a ser guardado
		p->next= 0; // 4º novo nó recebe o endereço "null", pois sendo uma pilha, esse novo nó simboliza o fim da pilha
	}
	return p;
}

void Node::desmonta_no (Node* p, Aluno* obj)
{
	*obj= p->D; // o ponteiro para o objeto aluno recebe o conteudo que estava  guardado em p
	delete p; // delete p, ou seja, deleta o new node apontado por p.
}

int main ()
{
	Aluno ze_ruela;
	Stack pilha_AA;
	string nome;
	int op= 1, mat;
	
	while(op>=1&&op<=5)
	{	
		cout << "1-Cadastrar.\n2-Mostrar.\n3-Retirar.\n4-Quantidade.\n5-Verifica se esta vazio.\nOutro numero - sair.\nCodigo: ";
		cin >> op;
		cout << "\n";
		if(op==1)
		{				
			cin.ignore();
			cout << "Nome: ";
			getline(cin, nome);			
			ze_ruela.set_Nome(nome);
			
			cout << "Matricula: ";
			cin >> mat;
			ze_ruela.set_Mat(mat);
			
			if(!pilha_AA.push(&ze_ruela))
			{
				cout << "\nNao foi possivel inserir o dado na pilha.\n\n";
			}
			else
			{
				cout << "\nDado inserido.\n\n";
			}
		}
		else
		{
			if (op==2)
			{
				if(pilha_AA.show(&ze_ruela))
				{
					cout << "\nNome: " << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";
				}
				else
				{
					cout << "\nNao foi possivel mostrar o dado da pilha.\n\n";
				}
			}
			else
			{
				if (op==3) 
				{
					if(!pilha_AA.pop(&ze_ruela))
					{
						cout << "\nPilha vazia.\n\n";
					}
					else
					{
						cout << "\nDado retirado.\n\n";	
					}					
				}
				else
				{
					if(op==4)
					{
						cout << "\nQuantidade de itens na pilha: " << pilha_AA.num_ele() << ".\n\n";
					}
					else
					{
						if(op==5)
						{
							if(pilha_AA.isempty())
							{
								cout << "\nPilha vazia.\n\n";
							}
							else
							{
								cout << "\nHa conteudo na pilha.\n\n";	
							}
						}
					}
				}				
			}
		}
	}
}

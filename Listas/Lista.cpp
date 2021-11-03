#include <iostream>

using namespace std;

// ++++++++++++ DeclaraÃ§Ã£o de classes ++++++++++++

class Aluno;
class List;
class Node;

// ++++++++++++ ImplementaÃ§Ã£o de classes ++++++++++++

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

class List
{
	private:
		Node* head;
		int qtd;
		
	public:
		List();
		~List();
		bool push(Aluno* obj);
		bool pop(Aluno* obj, int key);
		bool show(Aluno* obj, int key);
		bool isempty();	
		int num_ele();
};

class Node
{
	friend List;
	
	private:
		Aluno D; // guarda o objeto
		 	
	public:
		Node* next; // guarda o endereÃ§o do proximo nÃ³, que esta abaixo na pilha.
		Node();
		~Node();
		static Node* monta_no(Aluno* obj);
		static void desmonta_no(Node* p, Aluno* obj);	
};

//++++++++++++ ImplementaÃ§Ã£o dos mÃ©todos da classe Aluno ++++++++++++

Aluno::Aluno() 
{}

Aluno::~Aluno () 
{}

void Aluno::set_Nome (string nome)
{
	this->nome=nome; // usando "this" para nÃ£o dar erro por trabalhar com variaveis de mesmo nome
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

// ++++++++++++ ImplementaÃ§Ã£o dos mÃ©todos da classe List ++++++++++++

List::List()
{
	head= 0;
	qtd= 0;
}

List::~List()
{
	Node* p;
	while(head)
	{
		p= head;
		head= head->next; // head recebe o conteudo que esta em next, apontado por toheadp.
		delete p;	
	}
}

bool List::push(Aluno* obj)
{
	Node* p= Node::monta_no(obj);
	if(!p)
	{
		return false;
	}
	p->next= head;
	head= p;
	qtd++;
	return true;
}

bool List::pop(Aluno* obj, int key)
{
	Node** p= &head;
	while(*p && ((*p)->D).get_Mat()!=key)
	{
		p= &((*p)->next);
	}
	if(*p)
	{
		Node* aux= *p;
		*p= aux->next;
		Node::desmonta_no(aux, obj);
		qtd--;
		return true;
	}
	return false;
}

bool List::show(Aluno* obj, int key)
{
	if(!head)
	{
		return false;
	}	
	Node** p= &head;
	while(*p && ((*p)->D).get_Mat()!=key)
	{
		p= &((*p)->next);
	}
	if(*p)
	{
		*obj= ((*p)->D);
		return true;
	}
	return false;
}

int List::num_ele()
{
	return qtd;
}

bool List::isempty()
{
	return !head;
}

// ++++++++++++ Implementação dos métodos da classe Node ++++++++++++

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
	List lista_negra;
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
			
			if(!lista_negra.push(&ze_ruela))
			{
				cout << "\nNao foi possivel inserir o dado na lista.\n\n";
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
				cout << "Pesquise por matricula: ";
				cin >> mat;
				if(lista_negra.show(&ze_ruela, mat))
				{
					cout << "\nNome: " << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";
				}
				else
				{
					cout << "\nDado nao encontrado.\n\n";
				}
			}
			else
			{
				if (op==3) 
				{
					cout << "Pesquise por matricula: ";
					cin >> mat;
					if(!lista_negra.pop(&ze_ruela, mat))
					{
						cout << "\Lista vazia ou dado nao encontrado.\n\n";
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
						cout << "\nQuantidade de itens na lista: " << lista_negra.num_ele() << ".\n\n";
					}
					else
					{
						if(op==5)
						{
							if(lista_negra.isempty())
							{
								cout << "\nLista vazia.\n\n";
							}
							else
							{
								cout << "\nHa conteudo na lista.\n\n";	
							}
						}
					}
				}				
			}
		}
	}
}

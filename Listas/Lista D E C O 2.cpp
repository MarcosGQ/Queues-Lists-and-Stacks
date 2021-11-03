#include <iostream>

using namespace std;

// ++++++++++++ DeclaraÃ§Ã£o de classes ++++++++++++

class Aluno;
class List; // lista duplamente encadeada e ordenada. Eu nao sei / nao me lembro o que significa o "C". Versao 2
// explicação das listas: 
// https://www.treinaweb.com.br/blog/o-que-e-e-como-funciona-a-estrutura-de-dados-lista/#:~:text=As%20listas%20s%C3%A3o%20estruturas%20de,lista%20(dado%20o%20nome).&text=Um%20n%C3%B3%20%C3%A9%20uma%20estrutura,e%20as%20listas%20duplamente%20ligadas.
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
		Node* it;
		int qtd;
		
	public:
		List();
		~List();
		bool pushdeco(Aluno* obj);
		bool popdeco(Aluno* obj, int key);
		bool popdeco_NOsearch(Aluno* obj);
		bool search(Aluno* obj, int key);
		bool isempty();	
		int num_ele();
		void show_list();
		void it_mov_horario(Aluno* obj, int n);
		void it_mov_antihor(Aluno* obj, int n);
};

class Node
{
	friend List;

	private:
		Aluno D; // guarda o objeto
		 	
	public:
		Node* next; // guarda o endereÃ§o do proximo nÃ³, que esta abaixo na pilha.
		Node* prev;
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

bool List::pushdeco(Aluno* obj)
{
	Node* aux= Node::monta_no(obj);
	if(!aux)
	{
		return false;
	}
	if(!head)
	{
		aux->next= aux->prev= head= aux;
		it= head;
		qtd++;
		return true;
	}
	Node* p= head;
	if(((p->prev)->D).get_Mat() > obj->get_Mat() )
	{
		while( obj->get_Mat() > (p->D).get_Mat() )
		{
			p= p->next;
		}
	}
	aux->next= p;
	aux->prev= p->prev;
	(p->prev)->next= aux;
	p->prev= aux;
	if( obj->get_Mat() < head->D.get_Mat() )
	{
		head= aux;
	}
	qtd++;
	it= head;
	return true;
}

bool List::popdeco(Aluno* obj, int key)
{
	if(!search(obj, key))
	{
		return false;
	}
	if(it==it->next)
	{
		delete it;
		head= it= 0;
		qtd--;
		return true;
	}
	(it->next)->prev= it->prev;
	(it->prev)->next= it->next;
	if(it==head)
	{
		head= head->next;
	}
	delete it;
	it= head;
	qtd--;
	return true;
}

bool List::popdeco_NOsearch(Aluno* obj)
{
	if(head) // nesse metodo, a unica chance de dar erro, e se alista estiver vazia
	{
		if(head==head->next) // se aponta pra ele mesmo (apenas um item na lista)
		{
			delete head;
			head= it= 0;
			qtd--;
			return true;
		}
		(head->next)->prev= head->prev; // prev do proximo Node aquele que sera deletado apontara para o Node anterior do deletado
		(head->prev)->next= head->next; // next do Node anterior ao que sera deletado apontara para o Node apos aquele deletado
		if(it==head)
		{
			head= head->next;
		}
		delete it;
		it= head;
		qtd--;
		return true;
	}
	return false;
}

bool List::search(Aluno* obj, int key)
{
	if(!head)
	{
		return false;
	}	
	Node* p= head;
	int i= 0;
	while( key > (p->D).get_Mat() && (p!=head||!i) )
	{
		p= p->next;
		i++;
	}
	if(key==(p->D).get_Mat())
	{
		*obj= p->D;
		it= p;
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

void List::show_list()
{
	Node* p= head;
	int i= 0;
	if(head)
	{
		cout << "\nLista completa:\n";
		while(p!=head||!i)
		{
			cout << "Nome: " << p->D.get_Nome() << ".\nMatricula: " << p->D.get_Mat() << ".\n\n";
			p=p->next;
			i++;
		}
	}
	else
	{
		cout << "Lista vazia.\n\n";
	}
}

void List::it_mov_horario(Aluno* obj, int n)
{
	if(it)
	{
		for(int i= 0; i<n; i++)
		{
			it= it->next;
		}
		*obj= it->D;
	}
}

void List::it_mov_antihor(Aluno* obj, int n)
{
	if(it)
	{
		for(int i= 0; i<n; i++)
		{
			it= it->prev;
		}
		*obj= it->D;
	}
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
	
	while(op>=1&&op<=9)
	{	
		cout << "1-Cadastrar.\t\t2-Retirar.\n3-Mostrar item.\t\t4-Mostrar tudo\n5-Quantidade.\t\t6-Verifica vazio.\n7-Movimento horario.\t8-Movimento antihorario.\n9-Retira o primeiro.\t0-Fechar programa.\nCodigo: ";
		cin >> op;
		cout << "\n";
		switch(op)
		{
			case 1:
				cin.ignore();
				cout << "Nome: ";
				getline(cin, nome);			
				ze_ruela.set_Nome(nome);
				
				cout << "Matricula: ";
				cin >> mat;
				ze_ruela.set_Mat(mat);
				
				if(!lista_negra.pushdeco(&ze_ruela))
				{
					cout << "\nNao foi possivel inserir o dado na lista.\n\n";
				}
				else
				{
					cout << "\nDado inserido.\n\n";
				}
				break;
			
			case 2:
				cout << "Pesquise por matricula: ";
				cin >> mat;
				if(!lista_negra.popdeco(&ze_ruela, mat))
				{
					cout << "\nLista vazia ou dado nao encontrado.\n\n";
				}
				else
				{
					cout << "\nDado retirado:\nNome:" << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";	
				}
				break;	
								
			case 3:
				cout << "Pesquise por matricula: ";
				cin >> mat;
				if(lista_negra.search(&ze_ruela, mat))
				{
					cout << "\nDado encontrado:\nNome: " << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";
				}
				else
				{
					cout << "\nDado nao encontrado.\n\n";
				}
				break;
				
			case 4:
				lista_negra.show_list();
				break;
				
			case 5:
				cout << "\nQuantidade de itens na lista: " << lista_negra.num_ele() << ".\n\n";
				break;
				
			case 6:
				if(lista_negra.isempty())
				{
					cout << "Lista vazia.\n\n";
				}
				else
				{
					cout << "\nHa conteudo na lista.\n\n";	
				}
				break;
				
			case 7:
				cout << "Movimento horario: ";
				cin >> mat;
				lista_negra.it_mov_horario(&ze_ruela, mat);
				cout << "\nNome: " << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";	
				break;
				
			case 8:
				cout << "Movimento antihorario: ";
				cin >> mat;
				lista_negra.it_mov_antihor(&ze_ruela, mat);
				cout << "\nNome: " << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";	
				break;
				
			case 9:
				if(!lista_negra.popdeco_NOsearch(&ze_ruela))
				{
					cout << "\nLista vazia ou dado nao encontrado.\n\n";
				}
				else
				{
					cout << "\nDado apontado por head:\nNome: " << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";	
				}
				break;	
		}
	}
}

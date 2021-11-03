#include <iostream>

using namespace std;

// ++++++++++++ Declara��o de classes ++++++++++++

class Aluno;
class Queue; // Fila em ingles
class Node; // a fila vai "enfileirar" objetos da classe Node (n�) que contem o dado que iremos trabalhar

// ++++++++++++ Implementa��o de classes ++++++++++++

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

class Queue
{
	private:
		Node* head; // cabe�a
		Node* tail; // rabo
		int qtd; // quantidade de objetos na fila
		
	public:
		
		Queue();
		~Queue();
		bool push(Aluno* obj);
		bool pop(Aluno* obj);
		bool show(Aluno* obj);
		int num_ele();
		bool isempty();	
};

class Node
{
	friend Queue;
	
	private:
		Aluno D; // guarda o objeto
		 	
	public:
		Node* next; // guarda o endere�o do proximo n�, que esta abaixo na pilha.
		Node();
		~Node();
		static Node* monta_no(Aluno* obj);
		static void desmonta_no(Node* p, Aluno* obj);	
};

//++++++++++++ Implementa��o dos m�todos da classe Aluno ++++++++++++

Aluno::Aluno() 
{}

Aluno::~Aluno () 
{}

void Aluno::set_Nome (string nome)
{
	this->nome= nome; // usando "this" para n�o dar erro por trabalhar com variaveis de mesmo nome
}

void Aluno::set_Mat (int mat)
{
	this->mat= mat;
}

string Aluno::get_Nome ()
{
	return nome;
}

int Aluno::get_Mat ()
{
	return mat;
}

// ++++++++++++ Implementa��o dos m�todos da classe Stack ++++++++++++

Queue::Queue () // construtor que inicia a fila
{
	head= tail= 0; // inicialmente head e tail estao na primeira posicao da fila
	qtd= 0;
}

Queue::~Queue () 
{
	Node* p;
	while (head)
	{
		p= head;
		head= head->next; // head vai apontar para o objeto apontado por seu ponteiro "next", que aponta para o proximo objeto
		// ou seja, manda para 'p' o que quer deletar, e manda 'head' apontar para o proximo objeto, ele � o novo objeto na ponta da fila
		delete p;	
	}
}

bool Queue::push (Aluno* obj)
{
	Node* p= Node::monta_no(obj); // cria-se um ponteiro de Node que receber� o endere�o de p, criado no metodo monta_no. "p" aponta para o novo n� criado (new node).
	if (p) // verifica se foi possivel criar o n�
	{
		p->next= 0; // ultimo no sempre aponta para null
		if (!head) // se n�o ha head/se head � zero
		{
			head= p; // head sempre aponta para o primeiro elemento da fila
		}
		else
		{
			tail->next= p; // se h� mais de um objeto na fila, tail aponta para esse, que aponta para o proximo, ate o ultimo apontar para 0/null
		}
		tail= p;
		qtd++;
		return true;
	}
	return false;
}

bool Queue::pop (Aluno* obj)
{
	if (!head) // 1� verifica se a fila ta vazia
	{
		return false;
	}
	Node* p= head; // 2� - cria-se um ponteiro que receber� o endere�o do n� a ser removido
	head= head->next; // 3� - top aponta para o n� apontado por top, ou seja, top receber� o endere�o do n� que vem depois desse a ser removido
	if (!head) // se nao ha head, ou seja, se a fila ficou vazia apos a retirada
	{
		tail= 0;
	}
	Node::desmonta_no (p, obj); // 4� - chama m�todo para desmontar esse n�
	qtd--;
	return true; // 5� -  retorna true como um aviso de que tudo deu certo
}

bool Queue::show(Aluno* obj)
{
	if(!head)
	{
		return false;
	}	
	*obj= head->D;
	return true;
}

bool Queue::isempty()
{
	return !head;
}

int Queue::num_ele()
{
	return qtd;
}

// ++++++++++++ Implementa��o dos m�todos da classe Node ++++++++++++

Node::Node ()
{}

Node::~Node ()
{}

Node* Node::monta_no (Aluno* obj) // metodo que cria um novo n�
{
	Node* p= new Node; // 1� - cria-se um novo n� dinamico
	if (p) // 2� - verifica se foi criado o n�
	{
		p->D= *obj; // 3� - n� recebe o objeto a ser guardado
		p->next= 0; // 4� novo n� recebe o endere�o "null", pois sendo uma pilha, esse novo n� simboliza o fim da pilha
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
	Queue fila;
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
			
			if(!fila.push(&ze_ruela))
			{
				cout << "\nNao foi possivel inserir o dado na fila.\n\n";
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
				if(fila.show(&ze_ruela))
				{
					cout << "\nNome: " << ze_ruela.get_Nome() << "\nMatricula: " << ze_ruela.get_Mat() << ".\n\n";
				}
				else
				{
					cout << "\nNao foi possivel mostrar o dado da fila.\n\n";
				}
			}
			else
			{
				if (op==3) 
				{
					if(!fila.pop(&ze_ruela))
					{
						cout << "\nFila vazia.\n\n";
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
						cout << "\nQuantidade de itens na fila: " << fila.num_ele() << ".\n\n";
					}
					else
					{
						if(op==5)
						{
							if(fila.isempty())
							{
								cout << "\nFila vazia.\n\n";
							}
							else
							{
								cout << "\nHa conteudo na fila.\n\n";	
							}
						}
					}
				}				
			}
		}
	}
}

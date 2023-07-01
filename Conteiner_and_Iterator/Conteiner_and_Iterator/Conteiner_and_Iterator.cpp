#include <iostream>
#include <string>
#include <vector>






//struct Record {
//	std::string data;
//	int importance;
//};
//
//
//class MemoryCell {
//public:
//	virtual void SetData(std::string data) = 0;
//	std::string data = "пусто";
//};
//
//class Reflex : public MemoryCell {
//public:
//	virtual void SetData(std::string a) {
//		data = a;
//	}
//};
//
//class Desire : public MemoryCell {
//public:
//	virtual void SetData(std::string a) {
//		data = a;
//	}
//};
//
//class Idea : public MemoryCell {
//public:
//	virtual void SetData(std::string a) {
//		data = a;
//	}
//};



template <typename T>
class Conteiner {
private:

	struct Data {
		T data;
		Data* prev = nullptr;
		Data* next = nullptr;
	};

	Data* head = nullptr;
	Data* tail = nullptr;
	
	void push_first(T first) { head = new Data; head->data = first; head->prev = nullptr; head->next = nullptr; tail = head; }

public:
	struct Iterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using value_type = Data;
		using pointer = Data*;
		using reference = T;

		Iterator(pointer A) : point(A) {}
		Iterator(){}
		Iterator(const Iterator& A)		{ point = A.point; }
		Iterator(Iterator&& A) noexcept { point = A.point; A.point = nullptr; }
		~Iterator() {}

		reference operator*() const	{ return point->data; }
		reference operator[] (int i){
			pointer tmp = point;
			int j = 0;
			if (i > 0) {
				while ((j != i) && (tmp != nullptr)) {
					++j;
					tmp = tmp->next;
				}
			}
			else {
				while ((j != i) && (tmp != nullptr)) {
					++j;
					tmp = tmp->prev;
				}
			}
			if (tmp != nullptr) {
				return tmp->data;
			}
			return point->data;
		}

		pointer operator->() { return point; }

		Iterator& operator++(){ 
			if (point->next != nullptr) 
			{ 
				point = point->next; 
			} 
			return *this; 
		}


		Iterator& operator--(){ 
			if (point->prev != nullptr) 
			{ 
				point = point->prev; 
			}  
			return *this; 
		}

		Iterator operator+(int i){ 
			pointer tmp = point;
			int j = 0; 
			if (i > 0) {
				while ((j != i) && (tmp != nullptr)) {
					++j;
					tmp = tmp->next;
				}
			}
			else {
				while ((j != i) && (tmp != nullptr)) {
					--j;
					tmp = tmp->prev;
				}
			}
			if (tmp != nullptr) {
				point = tmp;
			}
			return *this; 
		}

		Iterator& operator+=(int i) {
			pointer tmp = point;
			int j = 0;
			if (i > 0) {
				while ((j != i) && (tmp != nullptr)) {
					++j;
					tmp = tmp->next;
				}
			}
			else {
				while ((j != i) && (tmp != nullptr)) {
					--j;
					tmp = tmp->prev;
				}
			}
			if (tmp != nullptr) {
				point = tmp;
			}
			return *this;
		}

		Iterator operator-(int i){ 
			pointer tmp = point;
			int j = 0; 
			if (i > 0) {
				while ((j != i) && (tmp != nullptr)) {
					++j;
					tmp = tmp->prev;
				}
			}
			else {
				while ((j != i) && (tmp != nullptr)) {
					--j;
					tmp = tmp->next;
				}
			}
			if (tmp != nullptr) {
				point = tmp;
			}
			return *this; 
		}

		Iterator& operator-=(int i) {
			pointer tmp = point;
			int j = 0;
			if (i > 0) {
				while ((j != i) && (tmp != nullptr)) {
					++j;
					tmp = tmp->prev;
				}
			}
			else {
				while ((j != i) && (tmp != nullptr)) {
					--j;
					tmp = tmp->next;
				}
			}
			if (tmp != nullptr) {
				point = tmp;
			}
			return *this;
		}

		friend bool operator== (const Iterator& a, const Iterator& b)  { return a.point == b.point; }
		friend bool operator!= (const Iterator& a, const Iterator& b)  { return a.point != b.point; }
		friend bool operator< (const Iterator& a, const Iterator& b) {
			pointer tmp = a.point;
			if (a.point == b.point ) {
				return false;
			}
			while (tmp != nullptr) {
				if (tmp == b.point) {
					return false;
				}
				tmp = tmp->prev;
			}
			return true;
		}

		friend bool operator> (const Iterator& a, const Iterator& b) {
			if (a.point == b.point ) {
				return false;
			}
			return !(a < b);
		}

		friend bool operator>= (const Iterator& a, const Iterator& b) { return !(a < b); }
		friend bool operator<= (const Iterator& a, const Iterator& b) { return !(a > b); }

		Iterator& operator=(const Iterator& other) { 
			if (this == &other)	{ 
				return *this; 
			} 
			point = other.point; 
			return *this; 
		}

		Iterator& operator=(Iterator&& other) noexcept {
			if (this == &other)	{ 
				return *this; 
			} 
			point = other.point; 
			other.point = nullptr; 
			return *this; 
		}

		void swap(Iterator& other) {
			pointer std = point;
			point = other.point;
			other.point = std;
		}

	private:
		pointer point = nullptr;
	};

	Conteiner()	{ };
	Conteiner(T first)				{
		head = new Data; 
		head->data = first; 
		head->prev = nullptr; 
		head->next = nullptr; 
		tail = head; 
	}

	Conteiner(T first, T second)    { 
		head = new Data; 
		head->data = first; 
		head->prev = nullptr; 
		tail = new Data; 
		head->next = tail; 
		tail->data = second; 
		tail->prev = head; 
		tail->next = nullptr; };

	Conteiner(Conteiner<T>& A) {
		Data* tmpT = this->head;
		Data* tmp_buf = nullptr;
		while (tmpT != nullptr) {
			this->head = this->head->next;
			delete tmpT;
			tmpT = this->head;
		}
		Data* tmpA = A.head;
		this->head = nullptr;
		this->tail = nullptr;
		if (tmpA != nullptr) {
			tmpT = new Data;
			tmpT->data = tmpA->data;
			tmpT->prev = nullptr;
			tmpT->next = nullptr;
			tmpA = tmpA->next;
			this->head = tmpT;
			tmp_buf = this->head;
		}
		while (tmpA != nullptr) {
			tmpT = new Data;
			tmpT->data = tmpA->data;
			tmpT->prev = tmp_buf;
			tmp_buf->next = tmpT;
			tmpT->next = nullptr;
			tmp_buf = tmpT;
			tmpA = tmpA->next;
		}
		this->tail = tmpT;
	}
	
	~Conteiner() {
		Data* tmp = nullptr;
		tmp = head;
		while (tmp != nullptr) {
			head = head->next;
			delete tmp;
			tmp = head;
		}
	}

	Iterator begin()  { return Iterator(head); }
	Iterator end()    { return Iterator(tail); }
	Iterator cbegin() { if (head != nullptr) { return Iterator(head->next); }return Iterator(); }
	Iterator cend()   { if (tail != nullptr) { return Iterator(tail->prev); }return Iterator(); }
	

	Conteiner<T>& operator=(Conteiner<T>& A)  {
		Data* tmpT = this->head;
		Data* tmp_buf = nullptr; 
		while (tmpT != nullptr) { 
			this->head = this->head->next; 
			delete tmpT; 
			tmpT = this->head; 
		}
		Data* tmpA = A.head;
		this->head = nullptr; 
		this->tail = nullptr;
		if (tmpA != nullptr){ 
			tmpT = new Data; 
			tmpT->data = tmpA->data; 
			tmpT->prev = nullptr; 
			tmpT->next = nullptr; 
			tmpA = tmpA->next; 
			this->head = tmpT; 
			tmp_buf = this->head; 
		}
		while (tmpA != nullptr) { 
			tmpT = new Data; 
			tmpT->data = tmpA->data; 
			tmpT->prev = tmp_buf; 
			tmp_buf->next = tmpT; 
			tmpT->next = nullptr; 
			tmp_buf = tmpT; 
			tmpA = tmpA->next; 
		}
		this->tail = tmpT;
		return *this;
	}

	T& operator[](int i) {
		int j = 0; 
		Data* tmp = head;
		while ((j != i) && (tmp != nullptr)) { 
			++j; 
			tmp = tmp->next; 
		} 
		if (tmp != nullptr)  return tmp->data;
		T R ;
		return R; 
	}

	void delite_elem(int i) {
		Data* tmp_buf = nullptr; int j = 0; Data* tmp =head; 
		while ((j != i) && (tmp != nullptr)) { ++j; tmp = tmp->next; }
		if (tmp != nullptr) {
			if ((tmp == head) && (tmp == tail)) { head = nullptr; tail = nullptr; delete tmp; }
			else if (tmp->next == nullptr) { tmp_buf = tmp->prev; tmp_buf->next = nullptr; delete tmp; tail = tmp_buf; }
			else if (tmp->prev == nullptr) { tmp_buf = tmp->next; tmp_buf->prev = nullptr; delete tmp; head = tmp_buf; }
			else { tmp_buf = tmp->next; tmp->prev->next = tmp_buf; tmp_buf->prev = tmp->prev; delete tmp; }
		}
	};

	void push_back(T A) {
		if (head == nullptr) { push_first(A); } 
		else { Data* tmp; tmp = new Data; tmp->data = A; tmp->next = nullptr; tmp->prev = tail; tail->next = tmp; tail = tmp; }
	}
	
	int size() { 
		int k = 0; Data* tmp = head; 
		while (tmp != nullptr) { k++; tmp = tmp->next; }
		return k; 
	}

	void swap(Conteiner<T>& A) {
		Data* tmpT = nullptr; 
		tmpT = A.head; A.head = this->head; this->head = tmpT;
		tmpT = A.tail; A.tail = this->tail; this->tail = tmpT; 
	}
	
	bool empty() { 
		return (size() == 0); 
	}

	friend bool operator== (Conteiner<T>& A, Conteiner<T>& B) {
		Data* tmpA = A.head;
		Data* tmpB = B.head;
		while (tmpA != nullptr || tmpB != nullptr) { 
			if (tmpA->data != tmpB->data)  return false; 
			tmpA = tmpA->next; 
			tmpB = tmpB->next; 
		} 
		if (tmpA == tmpB) return true; 
		return false; 
	}
	
	friend bool operator!= (Conteiner<T>& A, Conteiner<T>& B) { 
		return !(A == B); 
	}

};


class human
{
private:
	std::string name;
	int age;
	//std::vector <MemoryCell*> memories;
public:
	Conteiner <std::string> skills{ "плакать","есть" };


	human() {
		name = "Adam";
		age = 20;
	}

	human(std::string name, int age) {
		this->name = name;
		this->age = age;
	}

	void setname(std::string name) {
		this->name = name;
	}

	void print() {
		std::cout << name << "\n" << age << "\n";
	}

	/*void AddMemory(MemoryCell* a)
	{
		memories.push_back(a);
	}

	std::vector <MemoryCell*> GetMemory()
	{
		return memories;
	}*/
};







int main()
{
	setlocale(LC_ALL, "Russian");


	human first("ivan", 40);
	human a;
	/*first.print();
	a.print();
	a.AddMemory(new Reflex);
	a.AddMemory(new Idea);
	a.GetMemory()[1]->SetData("мысль");
	a.AddMemory(new Reflex);
	a.AddMemory(new Reflex);
	a.AddMemory(new Reflex);
	for (auto i : a.GetMemory()) {
		std::cout << i->data << "\n";
	}*/


	//выод элемента и замена знач
	std::cout << a.skills[0] << "\n";
	std::cout << a.skills[1] << "\n";
	std::cout << a.skills[2];
	a.skills[1] = "играть в доту";
	std::cout << a.skills[0] << "\n";
	std::cout << a.skills[1] << "\n";


	//Conteiner<int> test{ a.skills };

		//копирование по сылке
	//Conteiner<std::string> l{ a.skills };
	//std::cout << "\n" << "-------111------" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];
	//a.skills[1] = "думать";
	//std::cout << "\n" << "----" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];

	//копирование по значению
	Conteiner<std::string> l{"нет","да"};
	a.skills = l;
	std::cout << "\n" << "------222-------" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];
	a.skills[1] = "спать";
	std::cout << "\n" << "----" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];

	// итератор
	std::cout << "\n" << "------333-------" << "\n";
	std::cout << *l.begin() << "\n";
	std::cout << *++l.begin() << "\n";
	std::cout << (l.begin() == a.skills.begin()) << "\n";

	Conteiner<std::string>::Iterator It = l.begin();




	
	//добавление в контейнер
	Conteiner<std::string> F{};
	std::cout << "\n" << "------444-------" << "\n";
	for (int j = 0; j < F.size(); j++) { std::cout << F[j] << " "; }
	std::cout << "\n";
	F.push_back("биба");
	F.push_back("боба");
	F.push_back("3");
	F.push_back("4");
	for (int j = 0; j < F.size(); j++) { std::cout << F[j] << " "; }

	//логические действа
	std::cout << "\n" << "------555-------" << "\n";
	Conteiner<std::string> C{ "C" };
	F.swap(C);
	for (int j = 0; j < F.size(); j++) { std::cout << F[j] << " "; }
	std::cout << "\n";
	for (int j = 0; j < C.size(); j++) { std::cout << C[j] << " "; }

	std::cout << "\n" << (C == F);
	F = C;
	std::cout << "\n" << (C == F);
	std::cout << "\n" << C.empty();

	//удаление
	std::cout << "\n" << "------666-------" << "\n";
	for (int j = 0; j < C.size(); j++) { std::cout << C[j] << " "; }
	C.delite_elem(1);
	std::cout << "\n";
	for (int j = 0; j < C.size(); j++) { std::cout << C[j] << " "; }
	C.delite_elem(2);
	std::cout << "\n";
	for (int j = 0; j < C.size(); j++) { std::cout << C[j] << " "; }
	C.delite_elem(0);
	std::cout << "\n";
	for (int j = 0; j < C.size(); j++) { std::cout << C[j] << " "; }


	std::cout << "\n" << "------666-------" << "\n";
	Conteiner<int> c;
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	c.push_back(4);
	c.push_back(5);
	c.push_back(6);
	c.push_back(7);
	Conteiner<int>::Iterator I = c.begin();
	std::cout << "\n" << *I;
	std::cout << "\n" << *++I;
	std::cout << "\n" << *(I + 5);
	std::cout << "\n" << *(I + (-2)) << "\n";
	
}

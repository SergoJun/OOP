#include <iostream>
#include <string>
#include <vector>






struct Record {
	std::string data;
	int importance;
};


class MemoryCell {
public:
	virtual void SetData(std::string data) = 0;
	std::string data = "пусто";
};

class Reflex : public MemoryCell {
public:
	virtual void SetData(std::string a) {
		data = a;
	}
};

class Desire : public MemoryCell {
public:
	virtual void SetData(std::string a) {
		data = a;
	}
};

class Idea : public MemoryCell {
public:
	virtual void SetData(std::string a) {
		data = a;
	}
};


struct Count {
	int i = 1;
};

template <typename T>
class Conteiner {
private:

	struct Data {
		T data;
		Data* prev;
		Data* next;
	};

	Data* head = nullptr;
	Data* tail = nullptr;
	Data* tmp = nullptr;
	Data* tmp_buf = nullptr;
	T R;
	Count* count = nullptr;
	void push_first(T first) { head = new Data; head->data = first; head->prev = nullptr; head->next = nullptr; tail = head; }

public:
	struct Iterator
	{
		Data* point = nullptr;

		Iterator(Data* A) { point = A; }
		Iterator(const Iterator& A) { point = A.point; }
		Iterator(Iterator&& A) noexcept { point = A.point; A.point = nullptr; }

		T operator*() const { return point->data; }
		Data* operator->() { return point; }

		Iterator& operator++() { if (point->next != nullptr) { point = point->next; } return *this; }
		Iterator& operator--() { if (point->prev != nullptr) { point = point->prev; }  return *this; }
		Iterator& operator+(int i) { int j = 0; tmp = point; while ((j != i) && (tmp != nullptr)) { ++j; tmp = tmp->next; } if (tmp != nullptr) { point = tmp; }  return *this; }
		Iterator& operator-(int i) { int j = 0; tmp = point; while ((j != i) && (tmp != nullptr)) { ++j; tmp = tmp->prev; } if (tmp != nullptr) { point = tmp; }  return *this; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.point == b.point; }
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.point != b.point; }

		Iterator& operator=(const Iterator& other) { if (this == &other) { return *this; } point = other.point; return *this; }
		Iterator& operator=(Iterator&& other) noexcept { if (this == &other) { return *this; } point = other.point; other.point = nullptr; return *this; }
	};


	Conteiner() { head = nullptr; tail = nullptr; };
	Conteiner(T first) { head = new Data; head->data = first; head->prev = nullptr; head->next = nullptr; tail = head; }
	Conteiner(T first, T second) { head = new Data; head->data = first; head->prev = nullptr; tail = new Data; head->next = tail; tail->data = second; tail->prev = head; tail->next = nullptr; };
	~Conteiner() { if (count == nullptr || count->i == 1) { tmp = head; while (tmp != nullptr) { /*std::cout << " удалено ";*/ head = head->next; delete tmp; tmp = head; }if (count != nullptr) { delete count; count = nullptr; } }if (count != nullptr) { count->i--; } head = nullptr; tail = nullptr; }

	friend class Conteiner;
	template <class T3>
	Conteiner(Conteiner<T3>& A) { A.head = nullptr; A.tail = nullptr; }
	Conteiner(Conteiner<T>& A) { this->head = A.head;  this->tail = A.tail; if (A.count == nullptr) { A.count = new Count; A.count->i++; this->count = A.count; } else { A.count->i++; this->count = A.count; } }
	//Conteiner(Conteiner<T>&& A){ }
	//template <class T2> Conteiner(Conteiner<T2>&& A) { }

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(tail); }

	template <class T4>
	void operator=(Conteiner<T4>& A) { A.head = nullptr; A.tail = nullptr; }
	void operator=(Conteiner<T>& A) {
		this->tmp = this->head; if (this->count == nullptr || this->count->i == 1) {
			while (this->tmp != nullptr) { this->head = this->head->next; /*std::cout << " удалено ";*/ delete this->tmp; this->tmp = this->head; }
			if (this->count != nullptr) { delete this->count; this->count = nullptr; }
		}if (this->count != nullptr) { this->count->i--; this->head = nullptr; }A.tmp = A.head; this->head = nullptr; this->tail = nullptr;
		if (A.tmp != nullptr) { this->tmp = new Data; this->tmp->data = A.tmp->data; this->tmp->prev = nullptr; this->tmp->next = nullptr; A.tmp = A.tmp->next; this->head = this->tmp; this->tmp_buf = this->head; }
		while (A.tmp != nullptr) { this->tmp = new Data; this->tmp->data = A.tmp->data; this->tmp->prev = this->tmp_buf; this->tmp_buf->next = tmp; this->tmp->next = nullptr; this->tmp_buf = this->tmp; A.tmp = A.tmp->next; }this->tail = this->tmp;
	}

	T& operator[](int i) { int j = 0; tmp = head; while ((j != i) && (tmp != nullptr)) { ++j; tmp = tmp->next; } if (tmp != nullptr) { return tmp->data; }return R; }

	void delite_elem(int i) {
		int j = 0; tmp = head; while ((j != i) && (tmp != nullptr)) { ++j; tmp = tmp->next; } if (tmp != nullptr) {
			if ((tmp == head) && (tmp == tail)) { head = nullptr; tail = nullptr; delete tmp; }
			else if (tmp->next == nullptr) { tmp_buf = tmp->prev; tmp_buf->next = nullptr; delete tmp; tail = tmp_buf; }
			else if (tmp->prev == nullptr) { tmp_buf = tmp->next; tmp_buf->prev = nullptr; delete tmp; head = tmp_buf; }
			else { tmp_buf = tmp->next; tmp->prev->next = tmp_buf; tmp_buf->prev = tmp->prev; delete tmp; }
		}
	};
	void push_back(T A) { if (count == nullptr || count->i == 1) { if (head == nullptr) { push_first(A); } else { tmp = new Data; tmp->data = A; tmp->next = nullptr; tmp->prev = tail; tail->next = tmp; tail = tmp; } } }
	int size() { int k = 0; tmp = head; while (tmp != nullptr) { k++; tmp = tmp->next; }return k; }
	void swap(Conteiner<T>& A) { this->tmp = A.head; A.head = this->head; this->head = this->tmp; this->tmp = A.tail; A.tail = this->tail; this->tail = this->tmp; }
	friend bool operator== (Conteiner<T>& A, Conteiner<T>& B) { A.tmp = A.head; B.tmp = B.head; while (A.tmp != nullptr || B.tmp != nullptr) { if (A.tmp->data != B.tmp->data)  return false; A.tmp = A.tmp->next; B.tmp = B.tmp->next; } if (A.tmp == B.tmp) return true; return false; }
	friend bool operator!= (Conteiner<T>& A, Conteiner<T>& B) { return !(A == B); }
	bool empty() { return (size() == 0); }
};


class human
{
private:
	std::string name;
	int age;
	std::vector <MemoryCell*> memories;
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
	void AddMemory(MemoryCell* a)
	{
		memories.push_back(a);
	}
	std::vector <MemoryCell*> GetMemory()
	{
		return memories;
	}
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


	//	Conteiner<int> test{ a.skills };

		//копирование по сылке
	Conteiner<std::string> l{ a.skills };
	std::cout << "\n" << "-------111------" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];
	a.skills[1] = "думать";
	std::cout << "\n" << "----" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];

	//копирование по значению
	a.skills = l;
	std::cout << "\n" << "------222-------" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];
	a.skills[1] = "спать";
	std::cout << "\n" << "----" << "\n" << a.skills[0] << "\n" << a.skills[1] << "\n" << l[0] << "\n" << l[1];

	// итератор
	std::cout << "\n" << "------333-------" << "\n";
	std::cout << *l.begin() << "\n";
	std::cout << *++l.begin() << "\n";
	std::cout << (l.begin() == a.skills.begin()) << "\n";

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
}
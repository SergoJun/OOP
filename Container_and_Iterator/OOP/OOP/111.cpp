//#include <iostream>
//#include <vector>
//#include <array>
//#include <algorithm>
//
//
//
//class Processor {
//    std::string proccessorSocket;
//    int Hz;
//    int W;
//    public:   int Calc(int a, int b) {
//        a = a + b;
//        std::cout << a;
//        return a;
//    }
//};
//
//struct RAM {
//    friend bool operator==(RAM r1, RAM r2);
//    int MemoryAmount;
//    int HGz;
//};
//
//bool isRAMNotExist(RAM r) { return ((r.MemoryAmount == 0) && (r.HGz == 0)); }
//void makeRAMEmpty(RAM r) { r.MemoryAmount = 0; r.HGz = 0; }
//
//class Graphic_Card {
//    int AllMemory = 2048;
//    int usedMemory = 512;
//};
//
//
//
//class MotherBoard {
//    std::array <RAM, 4> ram = {};
//public:
//    std::ptrdiff_t getRamCount()
//    {
//        return std::count_if(ram.begin(), ram.end(), [](RAM elem) {return !isRAMNotExist(elem); });
//    }
//
//
//    void InsertRam(RAM g) {
//        for (int i = 0; i < 4; i++) {
//            if (isRAMNotExist(ram[i])) { ram[i] = g; break; }
//        }
//    }
//
//    RAM& GetRam(int n) {
//        return (ram[n]);
//    }
//
//    void RemoveRam(RAM g) {
//        for (int i = 0; i <= 4; i++) {
//            if (ram[i] == g) { makeRAMEmpty(ram[i]); }
//        }
//    }
//
//
//private:
//    std::string proccessorSlotSocket = "v1151";
//    bool haveProcessor = true;
//    bool haveGraphicCard = true;
//    int RAMSlotsBusy = 2;
//};
//
//struct EventArg
//{
//    int x;
//    int y;
//    int key;
//};
//
//class Device {
//public:
//    virtual void Input(EventArg) = 0;
//};
//
//class Mouse : public Device {
//    virtual void Input(EventArg e) {
//        std::cout << "Mouse loc " << e.x << " " << e.y;
//    }
//};
//
//class KeyBoard : public Device {
//    virtual void Input(EventArg  e) {
//        std::cout << "Key " << e.key;
//    }
//};
//
//
//class PC {
//    std::vector<Device*> Devices;
//  public: std::vector<Device*> GetDivice()
//{
//    return Devices;
//}
//      void AddDevice(Device* d) {
//          Devices.push_back(d);
//     }
//};
//
//
//bool operator==(RAM r1, RAM r2) {
//    return (r1.MemoryAmount == r2.MemoryAmount && r1.HGz == r2.HGz);
//}
//
//
//class ContainerRAM
//{
//public:
//    struct Iterator
//    {
//        using iterator_category = std::random_access_iterator_tag;
//        using value_type = RAM;
//        using pointer = RAM*;
//        using reference = RAM&;
//
//        Iterator(pointer ptr) : m_ptr(ptr) {}
//
//        Iterator() {}
//
//
//        Iterator(const Iterator& i) {
//            m_ptr = i.m_ptr;
//        }
//
//        Iterator(Iterator&& i) noexcept {
//            m_ptr = i.m_ptr;
//            i.m_ptr = nullptr;
//        }
//        reference operator*() const { return *m_ptr; }
//        pointer operator->() { return m_ptr; }
//        Iterator& operator++() { m_ptr++; return *this; }
//        Iterator& operator--() { m_ptr--; return *this; }
//        Iterator& operator+(int n) { m_ptr = m_ptr + n; return *this; }
//        Iterator& operator-(int n) { m_ptr = m_ptr - n; return *this; }
//        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
//        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }
//
//        Iterator& operator=(const Iterator& other) {
//            if (this == &other)
//                return *this;
//            m_ptr = other.m_ptr;
//            return *this;
//        }
//
//        Iterator& operator=(Iterator&& other) noexcept {
//            if (this == &other)
//                return *this;
//            m_ptr = std::move(other.m_ptr);
//            other.m_ptr = nullptr;
//            return *this;
//        }
//    private:
//        pointer m_ptr;
//    };
//
//public:
//    ContainerRAM() {}
//    Iterator begin() { return Iterator(&ram[0]); }
//    Iterator end() { return Iterator(&ram[4]); }
// //   Iterator cbegin() { return Iterator(&ram[0]); }
// //   Iterator cend() { return Iterator(&ram[4]); }
//    ContainerRAM(const ContainerRAM& d) { for (int i = 0; i < 3; i++) { ram[i] = d.ram[i]; } }
//    ContainerRAM(ContainerRAM&& d) { for (int i = 0; i < 3; i++) { ram[i] = d.ram[i]; makeRAMEmpty(d.ram[i]); } }
//    int size() { int size = 0; int n = 3; for (int i = 0; i < n; i++) { if (!isRAMNotExist(ram[i])) size++; return size; } }
//    int max_size() { return 4; }
//    bool empty() { return (size() == 0); }
//
//    ContainerRAM& operator=(const ContainerRAM& other) {
//        if (this == &other)
//            return *this;
//        else { for (int i = 0; i < 3; i++) { ram[i] = other.ram[i]; } }
//    }
//
//    ContainerRAM& operator=(ContainerRAM&& other) noexcept {
//        if (this == &other)
//            return *this;
//        else { for (int i = 0; i < 3; i++) { ram[i] = other.ram[i]; makeRAMEmpty(other.ram[i]); } }
//    }
//
//    friend bool operator== (const ContainerRAM& a, const ContainerRAM& b) { int size = 0; for (int i = 0; i < 3; i++) { if (a.ram[i] == b.ram[i]) size++; return (size == 4); } }
//    friend bool operator!= (const ContainerRAM& a, const ContainerRAM& b) { int size = 0; for (int i = 0; i < 3; i++) { if (a.ram[i] == b.ram[i]) size++; return (size != 4); } }
//
//    void swap(ContainerRAM& other) { ram.swap(other.ram); };
//
//private:
//    std::array <RAM, 4> ram = {};
//};
//      
//void swap(ContainerRAM& v1, ContainerRAM& v2) { v1.swap(v2); };
//
//int main()
//{
//    ContainerRAM A();
//    ContainerRAM B(À);
//}
//

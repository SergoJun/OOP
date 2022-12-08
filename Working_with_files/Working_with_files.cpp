
#include <iostream>
#include <string>
#include <fstream>




struct scan_info
{
	std::string model; // наименование модели
	int price; // цена
	double x_size; // горизонтальный размер области сканирования
	double y_size; // вертикальный размер области сканирования
	int optr; // оптическое разрешение
	int grey; // число градаций серого
};


void Masiv(scan_info **&arr, int i) {
	arr[i] = new scan_info;
	std::cout << "enter model" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, arr[i]->model);


	while (true) {
		std::cout << "enter price" << std::endl;
		std::cin >> arr[i]->price;
		if ((std::cin.fail()) || (arr[i]->price <= 0))
		{
			std::cin.clear();
			std::cout << "eror enter" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}

	while (true) {
		std::cout << "enter x_size" << std::endl;
		std::cin >> arr[i]->x_size;
		if ((std::cin.fail()) || (arr[i]->x_size <= 0))
		{
			std::cin.clear();
			std::cout << "eror enter" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}

	while (true) {
		std::cout << "enter y_size" << std::endl;
		std::cin >> arr[i]->y_size;
		if ((std::cin.fail()) || (arr[i]->y_size <= 0))
		{
			std::cin.clear();
			std::cout << "eror enter" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}
	while (true) {
		std::cout << "enter optr" << std::endl;
		std::cin >> arr[i]->optr;
		if ((std::cin.fail()) || (arr[i]->optr <= 0))
		{
			std::cin.clear();
			std::cout << "eror enter" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}
	while (true) {
		std::cout << "enter grey" << std::endl;
		std::cin >> arr[i]->grey;
		if ((std::cin.fail()) || (arr[i]->grey <= 0))
		{
			std::cin.clear();
			std::cout << "eror enter" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}
}


void Write(int n)
{

	std::ofstream fail("Bin.txt", std::ios_base::binary);
	scan_info **arr = new scan_info*[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new scan_info;
		Masiv(arr, i);
	}

	fail.write((char*)&n, sizeof(n));
	for (int i = 0; i < n; i++)
	{


		std::string::size_type l = arr[i]->model.size();

		fail.write((const char*)&l, sizeof(std::string::size_type));
		fail.write(arr[i]->model.c_str(), arr[i]->model.size());
		fail.write((char*)&arr[i]->price, sizeof(arr[i]->price));
		fail.write((char*)&arr[i]->x_size, sizeof(arr[i]->x_size));
		fail.write((char*)&arr[i]->y_size, sizeof(arr[i]->y_size));
		fail.write((char*)&arr[i]->optr, sizeof(arr[i]->optr));
		fail.write((char*)&arr[i]->grey, sizeof(arr[i]->grey));

	}

	fail.close();
	for (int i = 0; i < n; ++i)
	{
		delete arr[i];
	}
	delete[] arr;
}

void PrintFail() {
	int a;
	std::string::size_type l;
	std::ifstream fail("Bin.txt", std::ios_base::binary);
	if (!fail.is_open()) {
		std::cout << "open file eror\n";
		return;
	}
	fail.read((char*)&a, sizeof(a));
	scan_info **mas = new scan_info*[a];
	for (int i = 0; i < a; i++)
	{
		mas[i] = new scan_info;
		fail.read((char*)&l, sizeof(std::string::size_type));
		std::string sout(l, 0);

		for (int j = 0; j < l; ++j) {
			fail.read(&sout[j], sizeof(sout[0]));
		}
		mas[i]->model = sout;
		fail.read((char*)&mas[i]->price, sizeof(int));
		fail.read((char*)&mas[i]->x_size, sizeof(double));
		fail.read((char*)&mas[i]->y_size, sizeof(double));
		fail.read((char*)&mas[i]->optr, sizeof(int));
		fail.read((char*)&mas[i]->grey, sizeof(int));
	}
	std::wcout << std::endl;
	std::wcout << "-----------FILE------------" << std::endl;
	for (int i = 0; i < a; i++)
	{

		std::wcout << "----------- " << i+1 << " ElEM ------------" << std::endl;
		std::cout << "model:" << mas[i]->model << std::endl;
		std::cout << "price:" << mas[i]->price << std::endl;
		std::cout << "x_size:" << mas[i]->x_size << std::endl;
		std::cout << "y_size: " << mas[i]->y_size << std::endl;
		std::cout << "optr: " << mas[i]->optr << std::endl;
		std::cout << "grey: " << mas[i]->grey << std::endl;
	}
	std::wcout << std::endl;
	fail.close();
	for (int i = 0; i < a; ++i)
	{
		delete mas[i];
	}
	delete[] mas;
}

int Replacement(int num) {
	int a;
	std::string::size_type l;
	std::ifstream fail("Bin.txt", std::ios_base::binary);
	if (!fail.is_open()) {
		std::cout << "open file eror!\n";
		return 0;
	}
	fail.read((char*)&a, sizeof(a));

	if (num <= a) {
		scan_info **mas = new scan_info*[a];
		for (int i = 0; i < a; i++)
		{
			mas[i] = new scan_info;
			if ((i + 1) == num) {
				fail.read((char*)&l, sizeof(std::string::size_type));
				fail.seekg(l + 28, std::ios::cur);
				Masiv(mas, i);

			}
			else {

				fail.read((char*)&l, sizeof(std::string::size_type));
				std::string sout(l, 0);

				for (int j = 0; j < l; ++j) {
					fail.read(&sout[j], sizeof(sout[0]));
				}
				mas[i]->model = sout;
				fail.read((char*)&mas[i]->price, sizeof(int));
				fail.read((char*)&mas[i]->x_size, sizeof(double));
				fail.read((char*)&mas[i]->y_size, sizeof(double));
				fail.read((char*)&mas[i]->optr, sizeof(int));
				fail.read((char*)&mas[i]->grey, sizeof(int));
			}
		}
		fail.close();

		std::fstream clear_file("Bin.txt", std::ios_base::trunc);
		clear_file.close();


		std::ofstream fail("Bin.txt", std::ios_base::binary);

		fail.write((char*)&a, sizeof(a));
		for (int i = 0; i < a; i++)
		{
			std::string::size_type l = mas[i]->model.size();

			fail.write((const char*)&l, sizeof(std::string::size_type));
			fail.write(mas[i]->model.c_str(), mas[i]->model.size());
			fail.write((char*)&mas[i]->price, sizeof(mas[i]->price));
			fail.write((char*)&mas[i]->x_size, sizeof(mas[i]->x_size));
			fail.write((char*)&mas[i]->y_size, sizeof(mas[i]->y_size));
			fail.write((char*)&mas[i]->optr, sizeof(mas[i]->optr));
			fail.write((char*)&mas[i]->grey, sizeof(mas[i]->grey));

		}

		fail.close();
		for (int i = 0; i < a; ++i)
		{
			delete mas[i];
		}
		delete[] mas;
		return 0;
	}
	else {
		fail.close();
		return -1;
	}

}





int main() {
	int n, num;
	while (true) {
		std::cout << "enter amount" << std::endl;
		std::cin >> n;
		if ((std::cin.fail()) || (n <= 0))
		{
			std::cin.clear();
			std::cout << "eror enter" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}

	}
	Write(n);
	PrintFail();

	while (true) {
		std::cout << "enter replacement number" << std::endl;
		std::cin >> num;
		if ((std::cin.fail()) || (num <= 0))
		{
			std::cin.clear();
			std::cout << "eror enter" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}

	}
	std::cout << Replacement(num);
	PrintFail();


}
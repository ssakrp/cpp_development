#include <iostream>

using namespace std;
class Matrix
{
	struct page
	{
		double info;
		page* next_in_str;
	};
	struct str
	{
		page* first_in_str = nullptr;
		page* last_in_str = nullptr;
		str* next_in_col;
		double& operator[](int j)                               // Индексация для вовзрата элемента
		{
			page* current = first_in_str;
			for (int k = 0; k < j; ++k)
				current = current->next_in_str;
			return current->info;
		}
	};
	int quan_of_col;
	int quan_of_str;
	str* first_in_col = nullptr;
	str* last_in_col = nullptr;
public:
	void add_page(str* st, double value)      // Добавление листа
	{
		page* newpage = new page;
		newpage->info = value;
		newpage->next_in_str = nullptr;
		if (st->first_in_str == nullptr)
			st->first_in_str = st->last_in_str = newpage;
		else
		{
			st->last_in_str->next_in_str = newpage;
			st->last_in_str = newpage;
		}
	}
	void add_str()       // Добавление строки
	{
		str* newstr = new str;
		newstr->next_in_col = nullptr;
		if (first_in_col == nullptr)
			first_in_col = last_in_col = newstr;
		else
		{
			last_in_col->next_in_col = newstr;
			last_in_col = newstr;
		}
	}
	void str_process(str* st, int iter = 1)             // Заполнение строки по умолчанию
	{
		cout << "Enter " << quan_of_col << " values for input in " << iter << " string" << endl;
		double value;
		for (int i = 0; i < quan_of_col; ++i)
		{
		str_process_again:
			cin >> value;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "You have entered an incorrect value. Try it again" << endl;
				goto str_process_again;
			}
			else
				add_page(st, value);
		}
		cin.ignore(32767, '\n');
	}
	Matrix(int strin, int col) : quan_of_str(strin), quan_of_col(col)
	{
		if (strin <= 0 || col <= 0)
			cout << "You can create a matrix only with positive quantity of string and column" << endl;
		else
		{
			for (int i = 0; i < quan_of_str; ++i)
			{
				add_str();
				str_process(last_in_col, i + 1);
			}
		}
	}
	Matrix() {}             // Конструктор по умолчанию
	Matrix(const Matrix& x) : quan_of_col(x.quan_of_col), quan_of_str(x.quan_of_str)
	{
		page* current_page;
		str* current_str = x.first_in_col;
		for (int i = 0; i < quan_of_str; ++i)
		{
			add_str();
			current_page = current_str->first_in_str;
			for (int j = 0; j < quan_of_col; ++j)
			{
				add_page(last_in_col, current_page->info);
				current_page = current_page->next_in_str;
			}
			current_str = current_str->next_in_col;
		}
	}
	~Matrix()
	{
		page* current_page;
		str* current_str;
		for (int i = 0; i < quan_of_str; ++i)
		{
			current_str = first_in_col;
			for (int j = 0; j < quan_of_col; ++j)
			{
				current_page = current_str->first_in_str;
				current_str->first_in_str = current_str->first_in_str->next_in_str;
				delete current_page;
			}
			current_str->last_in_str = nullptr;
			first_in_col = first_in_col->next_in_col;
			delete current_str;
		}
		last_in_col = nullptr;
	}
	void output_str(str* st)            //Вывод строки (для матрицы)
	{
		page* current = st->first_in_str;
		if (current != nullptr)
		{
			do
			{
				cout << current->info << " ";
				current = current->next_in_str;
			} while (current != nullptr);
			cout << endl;
		}
		else
			cout << "Error. You've tried to output an empty string" << endl;
	}
	void output_matrix()       // Вывод матрицы
	{
		str* current = first_in_col;
		do
		{
			output_str(current);
			current = current->next_in_col;
		} while (current != nullptr);
	}
	str operator[](int i)               //Индексация, возврат строки
	{
		str* current = first_in_col;
		for (int k = 0; k < i; ++k)
			current = current->next_in_col;
		return *current;
	}
	Matrix operator!()                     // Транспонирование
	{
		Matrix result;
		result.quan_of_col = quan_of_str;
		result.quan_of_str = quan_of_col;
		for (int i = 0; i < quan_of_col; ++i)
		{
			result.add_str();
			for (int j = 0; j < quan_of_str; ++j)
				result.add_page(result.last_in_col, (*this)[j][i]);
		}
		return result;
	}
	friend Matrix operator+(Matrix& A, Matrix& B);
	friend Matrix operator-(Matrix& A, Matrix& B);
	friend Matrix operator*(Matrix& A, Matrix& B);
};

class Alg_vector
{
	int dimension;
	struct page
	{
		double info;
		page* next;
	};
	page* first = nullptr;
	page* last = nullptr;
public:
	void add_page(double value)           // Добавить лист
	{
		page* newcomp = new page;
		newcomp->next = nullptr;
		newcomp->info = value;
		if (first == nullptr)
			first = last = newcomp;
		else
		{
			last->next = newcomp;
			last = newcomp;
		}
	}
	Alg_vector(int dim) : dimension(dim)
	{
		if (dimension <= 0)
			cout << "You can't create zero-demensional vector. Set the right demension" << endl;
		else
		{
			double value;
			cout << "Enter " << dimension << " components of vector" << endl;
			for (int i = 0; i < dimension; ++i)
			{
			vector_create:
				cin >> value;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "You have entered an incorrect value. Try it again" << endl;
					goto vector_create;
				}
				else
					add_page(value);
			}
			cin.ignore(32767, '\n');
		}
	}
	Alg_vector() {}                                      // Конструктор по умолчанию
	Alg_vector(const Alg_vector& x) : dimension(x.dimension)
	{
		page* current = x.first;
		for (int i = 0; i < dimension; ++i)
		{
			add_page(current->info);
			current = current->next;
		}
	}
	void output_vector()
	{
		page* current = first;
		if (current == nullptr)
			cout << "You've tried to output a zero-demensional vector" << endl;
		else
		{
			do
			{
				cout << current->info << " ";
				current = current->next;
			} while (current != nullptr);
			cout << endl;
		}
	}
	double& operator[](int i)
	{
		page* current = first;
		for (int k = 0; k < i; ++k)
			current = current->next;
		return current->info;
	}
	~Alg_vector()
	{
		page* current;
		for (int i = 0; i < dimension; ++i)
		{
			current = first;
			first = first->next;
			delete current;
		}
		last = nullptr;
	}
	friend Alg_vector operator+(Alg_vector& A, Alg_vector& B);
	friend Alg_vector operator-(Alg_vector& A, Alg_vector& B);
	friend Alg_vector operator*(Alg_vector& A, double B);
	friend Alg_vector operator*(double A, Alg_vector& B);
};

Matrix operator+(Matrix& A, Matrix& B)
{
	if (A.quan_of_col != B.quan_of_col || A.quan_of_str != B.quan_of_str)
		throw 1;
	else
	{
		Matrix result;
		result.quan_of_col = A.quan_of_col;
		result.quan_of_str = A.quan_of_str;
		for (int i = 0; i < result.quan_of_str; ++i)
		{
			result.add_str();
			for (int j = 0; j < result.quan_of_col; ++j)
				result.add_page(result.last_in_col, A[i][j] + B[i][j]);
		}
		return result;
	}
}

Matrix operator-(Matrix& A, Matrix& B)
{
	if (A.quan_of_col != B.quan_of_col || A.quan_of_str != B.quan_of_str)
		throw 1;
	else
	{
		Matrix result;
		result.quan_of_col = A.quan_of_col;
		result.quan_of_str = A.quan_of_str;
		for (int i = 0; i < result.quan_of_str; ++i)
		{
			result.add_str();
			for (int j = 0; j < result.quan_of_col; ++j)
				result.add_page(result.last_in_col, A[i][j] - B[i][j]);
		}
		return result;
	}
}

Matrix operator*(Matrix& A, Matrix& B)
{
	if (A.quan_of_col != B.quan_of_str)
		throw 1;
	else
	{
		Matrix result;
		result.quan_of_col = B.quan_of_col;
		result.quan_of_str = A.quan_of_str;
		double expr;
		for (int i = 0; i < A.quan_of_str; ++i)
		{
			result.add_str();
			for (int j = 0; j < B.quan_of_col; ++j)
			{
				expr = 0;
				for (int k = 0; k < A.quan_of_col; ++k)
					expr += A[i][k] * B[k][j];
				result.add_page(result.last_in_col, expr);
			}
		}
		return result;
	}
}

Alg_vector operator+(Alg_vector& A, Alg_vector& B)
{
	if (A.dimension != B.dimension)
		throw 1;
	else
	{
		Alg_vector result;
		result.dimension = A.dimension;
		for (int i = 0; i < result.dimension; ++i)
		{
			result.add_page(A[i] + B[i]);
		}
		return result;
	}
}

Alg_vector operator-(Alg_vector& A, Alg_vector& B)
{
	if (A.dimension != B.dimension)
		throw 1;
	else
	{
		Alg_vector result;
		result.dimension = A.dimension;
		for (int i = 0; i < result.dimension; ++i)
			result.add_page(A[i] - B[i]);
		return result;
	}
}

Alg_vector operator*(Alg_vector& A, double B)
{
	Alg_vector result;
	result.dimension = A.dimension;
	for (int i = 0; i < result.dimension; ++i)
		result.add_page(A[i] * B);
	return result;
}

Alg_vector operator*(double A, Alg_vector& B)
{
	return B * A;
}

int main(int argc, char* argv[])
{
	cout << "Welcome to the program. It was made by Sergei Soshnikov. \nIt can create matrices or algebraic vectors and process them." << endl;
	int choice_1;
	while (true)
	{
		cout << "Let's begin from creating. Choose \"1\" if you want to create two matrices. Choose \"2\" if you want to create two algebraic vectors. For aborting programm choose \"3\"." << endl;
		cin >> choice_1;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "You have entered an incorrect value. Try it again" << endl;
		}
		else if (choice_1 == 1)
		{
			cin.ignore(32767, '\n');
			cout << "You have chosen a creating of two matrices. Choose quantity of strings and columns of first matrix." << endl;
			int quantity_of_string1, quantity_of_column1;
		making_matrix1:
			cin >> quantity_of_string1 >> quantity_of_column1;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "You have entered an incorrect value. Try it again" << endl;
				goto making_matrix1;
			}
			else
				cin.ignore(32767, '\n');
			cout << "Now choose quantity of strings and columns of second matrix." << endl;
			int quantity_of_string2, quantity_of_column2;
		making_matrix2:
			cin >> quantity_of_string2 >> quantity_of_column2;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "You have entered an incorrect value. Try it again" << endl;
				goto making_matrix2;
			}
			else
				cin.ignore(32767, '\n');
			Matrix matrix1(quantity_of_string1, quantity_of_column1);
			Matrix matrix2(quantity_of_string2, quantity_of_column2);
			cout << "You have created two matrices" << endl;
			int choice_2;
			while (true)
			{
				cout << "If you want to transpose your first matrix, choose \" 1 \".\nIf you want to transpose your second matrix, choose \" 2 \".\nIf you want to output your first matrix, choose \" 3 \".\nIf you want to output your second matrix, choose \" 4 \".\nIf you want to sum your matrices, choose \" 5 \".\nIf you want to substract your matrices, choose \" 6 \".\nIf you want to multiply your matrices, choose \" 7 \".\nIf you want to restart the program, choose \" 8 \".\nIf you want to finish the program, choose \" 0 \"." << endl;
				cin >> choice_2;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "You have entered an incorrect value. Try it again" << endl;
				}
				else if (choice_2 == 1)
				{
					cin.ignore(32767, '\n');
					(!matrix1).output_matrix();
				}
				else if (choice_2 == 2)
				{
					cin.ignore(32767, '\n');
					(!matrix2).output_matrix();
				}
				else if (choice_2 == 3)
				{
					cin.ignore(32767, '\n');
					matrix1.output_matrix();
				}
				else if (choice_2 == 4)
				{
					cin.ignore(32767, '\n');
					matrix2.output_matrix();
				}
				else if (choice_2 == 5)
				{
					cin.ignore(32767, '\n');
					try
					{
						(matrix1 + matrix2).output_matrix();
					}
					catch (int)
					{
						cout << "You can't sum matrices with different sizes. Restart the program to change your matrices." << endl;
					}
				}
				else if (choice_2 == 6)
				{
					cin.ignore(32767, '\n');
					try
					{
						(matrix1 - matrix2).output_matrix();
					}
					catch (int)
					{
						cout << "You can't substract matrices with different sizes. Restart the program to change your matrices." << endl;
					}
				}
				else if (choice_2 == 7)
				{
					cin.ignore(32767, '\n');
					try
					{
						(matrix1 * matrix2).output_matrix();
					}
					catch (int)
					{
						cout << "You can't multiply matrices with different quantity of columns in first matrix and quantity of strings in second matrix. Restart the program to change your matrices." << endl;
					}
				}
				else if (choice_2 == 8)
				{
					cin.ignore(32767, '\n');
					cout << "The program has been restarted" << endl;
					break;
				}
				else if (choice_2 == 0)
				{
					cin.ignore(32767, '\n');
					cout << "The program has been finished" << endl;
					return 0;
				}
				else
				{
					cin.ignore(32767, '\n');
					cout << "You have entered an incorrect value. Try it again" << endl;
				}
			}
		}
		else if (choice_1 == 2)
		{
			cin.ignore(32767, '\n');
			cout << "You have chosen a creating of two vectors. Choose the dimension of first one." << endl;
			int dimen1, dimen2;
		making_vector1:
			cin >> dimen1;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "You have entered an incorrect value. Try it again" << endl;
				goto making_vector1;
			}
			else
				cin.ignore(32767, '\n');
			cout << "Now choose the dimension of second one." << endl;
		making_vector2:
			cin >> dimen2;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "You have entered an incorrect value. Try it again" << endl;
				goto making_vector2;
			}
			else
				cin.ignore(32767, '\n');
			Alg_vector alg_vector1(dimen1);
			Alg_vector alg_vector2(dimen2);
			cout << "Two vectors have been created" << endl;
			int choice_2;
			while (true)
			{
				cout << "If you want to output the first vector, choose \" 1 \".\nIf you want to output the second vector, choose \" 2 \".\nIf you want to sum your vectors, choose \" 3 \".\nIf you want to substract your vectors, choose \" 4 \".\nIf you want to multiply the first vector on number, choose \" 5 \".\nIf you want to multiply the second vector on number, choose \" 6 \".\nIf you want to restart the program, choose \" 7 \".\nIf you want to finish the program, choose \" 0 \"." << endl;
				cin >> choice_2;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "You have entered an incorrect value. Try it again" << endl;
				}
				else if (choice_2 == 1)
				{
					cin.ignore(32767, '\n');
					alg_vector1.output_vector();
				}
				else if (choice_2 == 2)
				{
					cin.ignore(32767, '\n');
					alg_vector2.output_vector();
				}
				else if (choice_2 == 3)
				{
					cin.ignore(32767, '\n');
					try
					{
						(alg_vector1 + alg_vector2).output_vector();
					}
					catch (int)
					{
						cout << "You can't sum vectors with different dimensions. Restart the program to change your vectors." << endl;
					}
				}
				else if (choice_2 == 4)
				{
					cin.ignore(32767, '\n');
					try
					{
						(alg_vector1 - alg_vector2).output_vector();
					}
					catch (int)
					{
						cout << "You can't substract vectors with different dimensions. Restart the program to change your vectors." << endl;
					}
				}
				else if (choice_2 == 5)
				{
					cin.ignore(32767, '\n');
					double num;
					cout << "Enter a number for multiplying on the first vector" << endl;
				mult_vector1:
					cin >> num;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(32767, '\n');
						cout << "You have entered an incorrect value. Try it again" << endl;
						goto mult_vector1;
					}
					else
						cin.ignore(32767, '\n');
					(alg_vector1 * num).output_vector();
				}
				else if (choice_2 == 6)
				{
					cin.ignore(32767, '\n');
					double num;
					cout << "Enter a number for multiplying on the second vector" << endl;
				mult_vector2:
					cin >> num;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(32767, '\n');
						cout << "You have entered an incorrect value. Try it again" << endl;
						goto mult_vector2;
					}
					else
						cin.ignore(32767, '\n');
					(alg_vector2 * num).output_vector();
				}
				else if (choice_2 == 7)
				{
					cin.ignore(32767, '\n');
					cout << "The program has been restarted" << endl;
					break;
				}
				else if (choice_2 == 0)
				{
					cin.ignore(32767, '\n');
					cout << "The program has been finished" << endl;
					return 0;
				}
				else
				{
					cin.ignore(32767, '\n');
					cout << "You have entered a wrong value. Try it again" << endl;
				}
			}
		}
		else if (choice_1 == 3)
		{
			cin.ignore(32767, '\n');
			cout << "You have chosen an aborting of the program. Good bye." << endl;
			return 0;
		}
		else
		{
			cin.ignore(32767, '\n');
			cout << "You have tapped incorrect value. Try it again." << endl;
		}
	}
	return 0;
}
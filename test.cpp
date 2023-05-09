#include <iostream>

#define MAX 1000

int tree[MAX] = { 0 };
int lazy[MAX] = { 0 };
int N = 0;
int array[MAX] = { 0 };

/*
	CurrentNode: hệ số của node hiện tại
	startIndex, endIndex: hệ số bắt đầu và kết thúc các phần từ trong node
	startQuery, endQuery: hệ số bắt đầu và kết thúc của đoạn cần thay đổi
	diff: độ thay đổi
*/
void CND(int CurrentNode, int startIndex, int endIndex, int startQuery, int endQuery, int diff)
{
	// Nếu node hiện tại có cập nhật chưa được xử lý 
	if (lazy[CurrentNode] != 0)
	{
		tree[CurrentNode] += (endIndex - startIndex + 1) * lazy[CurrentNode];

		// Kiểm tra node hiện tại có phải node lá hay không
		if (startIndex != endIndex)
		{
			// Cập nhật giá trị lazy của các node con
			lazy[CurrentNode * 2 + 1] += lazy[CurrentNode];
			lazy[CurrentNode * 2 + 2] += lazy[CurrentNode];
		}

		lazy[CurrentNode] = 0;
	}

	// Nằm ngoài phạm vi
	if (startIndex >= endIndex || startIndex > endIndex || endIndex < startQuery)
		return;

	// Nếu đoạn cần cập nhật bao gồm cả node
	if (startQuery <= startIndex && endIndex <= endQuery)
	{
		tree[CurrentNode] += (endIndex - startIndex + 1) * diff;

		// Kiểm tra node hiện tại có phải là node lá hay không
		if (startIndex != endIndex)
		{
			lazy[CurrentNode * 2 + 1] += diff;
			lazy[CurrentNode * 2 + 2] += diff;
		}

		return;
	}

	// Nếu node hiện tại có trùng với đoạn cần cập nhật nhưng không hoàn toàn nằm trong
	int mid = (startIndex + endIndex) / 2;
	CND(CurrentNode * 2 + 1, startIndex, mid, startQuery, endQuery, diff);
	CND(CurrentNode * 2 + 2, mid + 1, endIndex, startQuery, endQuery, diff);

	// Cập nhật node hiện tại
	tree[CurrentNode] = tree[CurrentNode * 2 + 1] + tree[CurrentNode * 2 + 2];
}

void CapNhatDoan(int n, int startQuery, int endQuery, int diff)
{
	CND(0, 0, n - 1, startQuery, endQuery, diff);
}


int LT(int CurrentNode, int startIndex, int endIndex, int startQuery, int endQuery)
{
	// Nếu node hiện tại có cập nhật đang chờ
	if (lazy[CurrentNode] != 0)
	{
		tree[CurrentNode] += (endIndex - startIndex + 1) * lazy[CurrentNode];

		// Kiểm tra có phải node lá hay không
		if (startIndex != endIndex)
		{
			lazy[CurrentNode * 2 + 1] += lazy[CurrentNode];
			lazy[CurrentNode * 2 + 2] += lazy[CurrentNode];
		}

		lazy[CurrentNode] = 0;
	}

	// Nằm ngoài phạm vi
	if (startIndex > endIndex || startIndex > endQuery || endIndex < startQuery)
		return 0;

	// Nếu node hiện tại nằm trong khoảng cần lấy tổng
	if (startQuery <= startIndex && endIndex <= endQuery)
		return tree[CurrentNode];

	// Nếu node hiện tại có trùng với đoạn cần cập nhật nhưng không hoàn toàn nằm trong
	int mid = (startIndex + endIndex) / 2;
	return LT(CurrentNode * 2 + 1, startIndex, mid, startQuery, endQuery) + LT(CurrentNode * 2 + 2, mid + 1, endIndex, startQuery, endQuery);
}

int LayTong(int n, int startQuery, int endQuery)
{
	return LT(0, 0, n - 1, startQuery, endQuery);
}

void TC(int arr[], int CurrentNode, int startIndex, int endIndex)
{
	if (startIndex > endIndex)
		return;

	// Nếu có một phần tử trong mảng
	if (startIndex == endIndex)
	{
		tree[CurrentNode] = arr[startIndex];
		return;
	}

	// Nếu có nhiều hơn một phần tử
	int mid = (startIndex + endIndex) / 2;
	TC(arr, CurrentNode * 2 + 1, startIndex, mid);
	TC(arr, CurrentNode * 2 + 2, mid + 1, endIndex);

	tree[CurrentNode] = tree[CurrentNode * 2 + 1] + tree[CurrentNode * 2 + 2];
}

void TaoCay(int arr[], int n)
{
	TC(arr, 0, 0, n - 1);
}

void InMenu()
{
	std::cout << "Chon thao tac:\n";
	std::cout << "\tTao cay: nhan 1\n";
	std::cout << "\tCap nhat doan: nhan 2\n";
	std::cout << "\tLay tong: nhan 3\n";
	std::cout << "\tThoat: nhan so bat ky\n";
}

void Output(int a[], int n)
{
	for (int i = 0; i < n; i++)
		std::cout << a[i] << "\t";
	std::cout << "\n";
}
void Menu()
{
	while (1)
	{
		int start;
		int end;
		int diff;

		int m = 0;

		InMenu();

		std::cin >> m;

		switch (m)
		{
		case 1:
			std::cout << "Nhap so luong phan tu cua mang: ";
			std::cin >> N;

			for (int i = 0; i < N; ++i)
			{
				std::cout << "Nhap phan tu thu " << i << ": ";
				std::cin >> array[i];
			}

			TaoCay(array, N);
			Output(tree, 2*N + 1);
			break;
		case 2:
			

			do
			{
				std::cout << "Nhap he so bat dau: ";
				std::cin >> start;

				std::cout << "Nhap he so ket thuc: ";
				std::cin >> end;

				std::cout << "Nhap luong can thay doi: ";
				std::cin >> diff;
			} while (end < start);

			CapNhatDoan(N, start, end, diff);
			Output(tree, 2*N + 1);
			Output(lazy, 2 * N + 1);
			break;
		case 3:
		
			do
			{
				std::cout << "Nhap he so bat dau: ";
				std::cin >> start;

				std::cout << "Nhap he so ket thuc: ";
				std::cin >> end;
			} while (end < start);

			std::cout << LayTong(N, start, end) << "\n";

			break;
		default:
			return;
		}
	}
}


int main()
{
	Menu();

	return 0;
}
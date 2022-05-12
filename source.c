#define _CRT_SECURE_NO_WARNINGS	//�⺻
#define size 19

#define FullSize 500
#define tempSize 200

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StoneStack_ {
	int x;
	int y;
	int color;

	struct StoneStack_* next;
} StoneStack;

typedef struct contStone_ {
	char startx;
	char starty;
	char endx;
	char endy;
	char color;
	char length;
	char isempty;
} contStone;

void empty();
void black();
void white();
void specialblack();
void specialwhite();
void danger();
void prt(int i, int j);		//i�� j���� ��翡 ���� ���
void boardprt();			//������ ��ü ���
void set(StoneStack** mainsp, StoneStack** undosp);				//������ �� �� �α�
void bwcount();				//������ ��ü�� �򵹰� �������� �� ���� ����

void rc_cntstone();			//�� �����ٰ� �������� ������, �� ���� ���
void maxcont_stone();		//�� ����, �����ٿ��� �ִ�� ���ӵ� �� ���
void maxcontdiag_stone();	//�� �밢������ �ִ�� ���ӵ� �� ���

void specialreset();		//���ٲ� �ٵϵ� �������·� �����°�
contStone* maxcontview(char option);			//1: ��ĭ���� �ִ뿬�ӵ��� ��ǥ������ ��ȯ or 2: length�� 3, 4�� ��ǥ ��ȯ
void changeStone(contStone* data);		//���ӵ� ��ǥ ��� �ٲ��ֱ�
void prtcontStone(contStone* data);		//���ӵ� ��ǥ ���

void checkstop(contStone* data);

StoneStack Pop(StoneStack** sp);
void Push(StoneStack** sp, StoneStack data);
void Load(StoneStack** mainsp, StoneStack** undosp);
void Save(StoneStack* mainsp, StoneStack* undosp);
void Reset(StoneStack** sp);						//������ ��� ������ ����

int board[size][size] = {
	{ 0, 0, 1, 0, 1, 0, 2, 2, 1, 2, 0, 2, 2, 0, 0, 0, 1, 0, 0 },
	{ 1, 2, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1, 0 },
	{ 0, 0, 2, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 2, 2, 0, 1, 0, 1 },
	{ 0, 2, 0, 1, 0, 1, 1, 0, 1, 2, 0, 1, 0, 2, 0, 2, 1, 0, 0 },
	{ 2, 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 1, 0, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 1, 2, 0 },
	{ 1, 0, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 1, 1, 1, 0, 0 },
	{ 0, 1, 1, 2, 0, 0, 0, 2, 2, 0, 0, 1, 1, 2, 1, 1, 1, 0, 0 },
	{ 1, 1, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 1, 2, 0, 1, 0, 1 },
	{ 0, 1, 0, 0, 0, 0, 2, 1, 0, 0, 1, 2, 0, 0, 1, 0, 0, 2, 0 },
	{ 1, 0, 0, 0, 2, 0, 2, 0, 2, 2, 0, 1, 0, 0, 1, 0, 1, 0, 2 },
	{ 1, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 1, 1, 0, 2, 0 },
	{ 0, 2, 0, 1, 2, 0, 0, 2, 0, 1, 1, 1, 0, 1, 1, 0, 2, 0, 0 },
	{ 0, 0, 2, 0, 0, 2, 0, 2, 1, 1, 0, 1, 0, 2, 1, 1, 0, 2, 0 },
	{ 2, 0, 0, 0, 0, 1, 0, 2, 1, 0, 0, 1, 2, 0, 1, 1, 2, 0, 0 },
	{ 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 0, 0 },
	{ 2, 0, 2, 0, 0, 1, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 2 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
};

int count, bcount, wcount;
int start = 1;

int main(void)
{
	StoneStack* Stone = NULL;
	StoneStack* Undo = NULL;
	while (start) {
		boardprt();
		set(&Stone, &Undo);
	}

	exit(0);
	return 0;
}


void empty() {
	printf("�� ");
}

// 1�� ��
void black() {
	printf("��");
}

// 2�� ȭ��Ʈ
void white() {
	printf("��");
}

//Ư����
void specialblack() {
	printf("��");
}

//Ư��ȭ��Ʈ
void specialwhite() {
	printf("��");
}

void danger()
{
	printf("��");
}


void prt(int i, int j) {
	switch (board[i][j]) {
	case 0:
		empty();
		break;
	case 1:
		black();
		break;
	case 2:
		white();
		break;
	case 3:
		specialblack();
		break;
	case 4:
		specialwhite();
		break;
	case 5:
		danger();
		break;
	default:
		printf("X");
		break;
	}
}

void boardprt() {
	specialreset();
	checkstop(maxcontview(2));
	changeStone(maxcontview(1));

	bwcount();

	printf("   0 1 2 3 4 5 6 7 8 9 101112131415161718\n");
	for (int i = 0; i < size; i++)
	{
		printf("%2d ", i);
		for (int j = 0; j < size; j++)
		{
			prt(i, j);
		}
		printf("\n");
	}
	printf("���� �� : %d��, �� �� : %d��\n\n", bcount, wcount);
}

void set(StoneStack** mainsp, StoneStack** undosp) {
	while (1) {
		int order = 0;

		printf("-------------------------------------------------\n");
		printf("1 : ��ǥ �Է�\n");
		printf("2 : ������/���������\n");
		printf("3 : ���� �ʱ�ȭ\n");
		printf("4 : ���� ���� �ҷ�����\n");
		printf("5 : �����ϱ�\n");
		printf("6 : ���� �� ����\n");
		printf("7 : �������� �ʰ� ����\n");
		printf("8 : �ٵ��� ���� ���\n");
		printf("-------------------------------------------------\n");

		printf("�޴��� ������ �ּ��� : ");
		if (scanf("%d", &order) < 1) {
			printf("�ٽ� �Է��� �ּ���\n");
			while (getchar() != '\n');
			continue;
		}
		switch (order) {
		case 1:
			while (1) {
				int x, y;
				if (!(count % 2))
					printf("���� ");
				else if (count % 2)
					printf("�� ");
				printf("���� ���� ��ǥ�� �Է��ϼ��� (x y) : ");
				while (getchar() != '\n');
				if (scanf("%d %d", &x, &y) < 2) {
					printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n\n");
					while (getchar() != '\n');
					continue;
				}
				if (x < 0 || x>18 || y < 0 || y>18) {
					printf("x, y�� ������ 0~18�Դϴ�. �ٽ� �Է��� �ּ���.\n\n");
					continue;
				}
				if (board[x][y] != 0 && board[x][y] != 5) {
					printf("�̹� ���� ������ �ֽ��ϴ�. �ٽ� �Է��� �ּ���.\n\n");
					continue;
				}

				if (!(count % 2)) {
					board[x][y] = 1;
					StoneStack temp = { x, y, 1, NULL };
					Push(mainsp, temp);
					Reset(undosp);
				}
				else if (count % 2) {
					board[x][y] = 2;
					StoneStack temp = { x, y, 2, NULL };
					Push(mainsp, temp);
					Reset(undosp);
				}
				break;
			}
			break;
		case 2:
			while (1) {
				char num;
				printf("U : ������ || R : ������ ���\n");
				printf("�Է��� �ּ��� : ");
				while (getchar() != '\n');
				if (scanf("%c", &num) < 1) {
					printf("�ٽ� �Է��� �ּ���\n\n");
					continue;
				}
				switch (num) {
				case 'U': {
					StoneStack temp = Pop(mainsp);
					if (temp.x == -1) {
						printf("�� �̻� ���� �� �����ϴ�.\n");
						system("pause");
						break;
					}
					Push(undosp, temp);
					board[temp.x][temp.y] = 0;
					break; }
				case 'R': {
					StoneStack temp = Pop(undosp);
					if (temp.x == -1) {
						printf("���� ���� �����ϴ�.\n");
						system("pause");
						break;
					}
					Push(mainsp, temp);
					board[temp.x][temp.y] = temp.color;
					break; }
				default:
					printf("�ٽ� �Է��� �ּ���\n\n");
					continue;
					break;
				}
				break;
			}
			break;
		case 3:
			Reset(mainsp);
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					board[i][j] = 0;
			Reset(undosp);
			break;
		case 4:
			Reset(mainsp);
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					board[i][j] = 0;
			Reset(undosp);
			Load(mainsp, undosp);
			break;
		case 5:
			Save(*mainsp, *undosp);
			break;
		case 6:
			Save(*mainsp, *undosp);
			start = 0;
			return;
		case 7:
			start = 0;
			return;
		case 8:
			system("cls");
			rc_cntstone();
			maxcont_stone();
			maxcontdiag_stone();
			prtcontStone(maxcontview(1));
			return;
		default:
			printf("�ٽ� �Է��� �ּ���\n");
			system("pause");
			break;
		}
		system("cls");
		break;
	}
}

void bwcount()
{
	bcount = 0;
	wcount = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == 1 || board[i][j] == 3)
				bcount++;
			else if (board[i][j] == 2 || board[i][j] == 4)
				wcount++;
		}
	}
	count = bcount + wcount;
}

void rc_cntstone()
{
	printf("-----------�� ��� ���� ������, �� ����-----------\n");
	int rowbtemp = 0, rowwtemp = 0, colbtemp = 0, colwtemp = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			switch (board[i][j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				rowbtemp++;
				break;
			case 2:
			case 4:
				rowwtemp++;
				break;
			}
		}
		for (int j = 0; j < size; j++) {
			switch (board[j][i]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				colbtemp++;
				break;
			case 2:
			case 4:
				colwtemp++;
				break;
			}
		}

		printf("%2d�� ���� �� : %2d��, �� �� : %2d��	| %2d�� ���� �� : %2d��, �� �� : %2d��\n", i, rowbtemp, rowwtemp, i, colbtemp, colwtemp);

		rowbtemp = 0; rowwtemp = 0; colbtemp = 0; colwtemp = 0;
	}
	printf("\n");
}

void maxcont_stone()
{
	printf("-----------�� ��� ������ ���� ���� ���ӵ� �� ���-----------\n");
	int btemp = 1, wtemp = 1, rowb_max = 0, roww_max = 0, colb_max = 0, colw_max = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			switch (board[i][j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[i][j + 1] == 1 || board[i][j + 1] == 3) {
					btemp++;
					if (btemp > rowb_max)
						rowb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[i][j + 1] == 2 || board[i][j + 1] == 4) {
					wtemp++;
					if (wtemp > roww_max)
						roww_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		for (int j = 0; j < size - 1; j++) {
			switch (board[j][i]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][i] == 1 || board[j + 1][i] == 3) {
					btemp++;
					if (btemp > colb_max)
						colb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[j + 1][i] == 2 || board[j + 1][i] == 4) {
					wtemp++;
					if (wtemp > colw_max)
						colw_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		printf("%2d�� MAX : ", i);
		if (rowb_max > roww_max)
			printf("����, %2d��		", rowb_max);
		else if (rowb_max < roww_max)
			printf("���, %2d��		", roww_max);
		else if (rowb_max == roww_max && rowb_max != 0)
			printf("[����, ���], %2d��	", rowb_max);
		else
			printf("���ӵ� �� ����	");

		printf("| %2d�� MAX : ", i);
		if (colb_max > colw_max)
			printf("����, %2d��\n", colb_max);
		else if (colb_max < colw_max)
			printf("���, %2d��\n", colw_max);
		else if (colb_max == colw_max && colb_max != 0)
			printf("[����, ���], %2d��\n", colb_max);
		else
			printf("���ӵ� �� ����\n");


		rowb_max = 0; roww_max = 0; colb_max = 0; colw_max = 0; btemp = 1; wtemp = 1;
	}
	printf("\n");
}

void maxcontdiag_stone()
{
	printf("-----------�� �밢������ ���� ���� ���ӵ� �� ���-----------\n");
	int btemp = 1, wtemp = 1, rowb_max = 0, roww_max = 0, colb_max = 0, colw_max = 0;


	printf("------------------------------------------------------------\n");
	printf("	(��)���� �밢��.	��, ���� �밢���� ���� ��ġ\n");
	printf("	0��� 0���� ���� �밢���Դϴ�.\n");
	printf("------------------------------------------------------------\n");

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < i; j++) {
			switch (board[size - 1 - i + j][j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[size - i + j][j + 1] == 1 || board[size - i + j][j + 1] == 3) {
					btemp++;
					if (btemp > rowb_max)
						rowb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[size - i + j][j + 1] == 2 || board[size - i + j][j + 1] == 4) {
					wtemp++;
					if (wtemp > roww_max)
						roww_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		for (int j = 0; j < size - i - 1; j++) {
			switch (board[j][j + i]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][j + i + 1] == 1 || board[j + 1][j + i + 1] == 3) {
					btemp++;
					if (btemp > colb_max)
						colb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[j + 1][j + i + 1] == 2 || board[j + 1][j + i + 1] == 4) {
					wtemp++;
					if (wtemp > colw_max)
						colw_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		printf("%2d�� MAX : ", size - 1 - i);
		if (rowb_max > roww_max)
			printf("����, %2d��		", rowb_max);
		else if (rowb_max < roww_max)
			printf("���, %2d��		", roww_max);
		else if (rowb_max == roww_max && rowb_max != 0)
			printf("[����, ���], %2d��	", rowb_max);
		else
			printf("���ӵ� �� ����	");

		printf("| %2d�� MAX : ", i);
		if (colb_max > colw_max)
			printf("����, %2d��\n", colb_max);
		else if (colb_max < colw_max)
			printf("���, %2d��\n", colw_max);
		else if (colb_max == colw_max && colb_max != 0)
			printf("[����, ���], %2d��\n", colb_max);
		else
			printf("���ӵ� �� ����\n");


		rowb_max = 0; roww_max = 0; colb_max = 0; colw_max = 0; btemp = 1; wtemp = 1;
	}



	printf("------------------------------------------------------------\n");
	printf("	(��)���� �밢��.	��, ���� �밢���� ���� ��ġ\n");
	printf("	18���� 0���� ���� �밢���Դϴ�.\n");
	printf("------------------------------------------------------------\n");

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
			switch (board[j][i - j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][i - j - 1] == 1 || board[j + 1][i - j - 1] == 3) {
					btemp++;
					if (btemp > rowb_max)
						rowb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[j + 1][i - j - 1] == 2 || board[j + 1][i - j - 1] == 4) {
					wtemp++;
					if (wtemp > roww_max)
						roww_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		for (int j = 0; j < size - i - 1; j++) {
			switch (board[i + j][size - 1 - j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[i + j + 1][size - 2 - j] == 1 || board[i + j + 1][size - 2 - j] == 3) {
					btemp++;
					if (btemp > colb_max)
						colb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[i + j + 1][size - 2 - j] == 2 || board[i + j + 1][size - 2 - j] == 4) {
					wtemp++;
					if (wtemp > colw_max)
						colw_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		printf("%2d�� MAX : ", i);
		if (rowb_max > roww_max)
			printf("����, %2d��		", rowb_max);
		else if (rowb_max < roww_max)
			printf("���, %2d��		", roww_max);
		else if (rowb_max == roww_max && rowb_max != 0)
			printf("[����, ���], %2d��	", rowb_max);
		else
			printf("���ӵ� �� ����	");

		printf("| %2d�� MAX : ", i);
		if (colb_max > colw_max)
			printf("����, %2d��\n", colb_max);
		else if (colb_max < colw_max)
			printf("���, %2d��\n", colw_max);
		else if (colb_max == colw_max && colb_max != 0)
			printf("[����, ���], %2d��\n", colb_max);
		else
			printf("���ӵ� �� ����\n");


		rowb_max = 0; roww_max = 0; colb_max = 0; colw_max = 0; btemp = 1; wtemp = 1;
	}
	printf("\n");
}

void specialreset() {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			if (board[i][j] > 2 && board[i][j] <= 4)
				board[i][j] -= 2;
			else if (board[i][j] > 4)
				board[i][j] = 0;
		}
}

contStone* maxcontview(char option)
{
	contStone Stonedata[FullSize] = { 0 };
	int dataindex = 0;

	int max = 0;



	//������
	contStone tempcontrow[tempSize] = { 0 };
	int tempindex = 0;

	int temp = 1;

	for (int i = 0; i < size; i++) {			//��, ������ ��� ���� ��ü �����ٿ��� 1�� �̻� ������ ���� ������ ����
		for (int j = 0; j < size - 1; j++) {
			switch (board[i][j]) {
			case 0:
			case 5:
				if (j == size - 2) {
					if (board[i][j + 1] == 1 || board[i][j + 1] == 3) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 1;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[i][j + 1] == 2 || board[i][j + 1] == 4) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 2;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[i][j + 1] == 1 || board[i][j + 1] == 3) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 1;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontrow[tempindex].startx = i;
					tempcontrow[tempindex].starty = j - temp + 1;
					tempcontrow[tempindex].endx = i;
					tempcontrow[tempindex].endy = j;
					tempcontrow[tempindex].color = 1;
					tempcontrow[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[i][j + 1] == 2 || board[i][j + 1] == 4) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 2;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontrow[tempindex].startx = i;
					tempcontrow[tempindex].starty = j - temp + 1;
					tempcontrow[tempindex].endx = i;
					tempcontrow[tempindex].endy = j;
					tempcontrow[tempindex].color = 2;
					tempcontrow[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontrow[i].length != 0; i++) {						//tempcontrow�� ����Ǿ� �ִ� ���ӵ� �߿��� length�� max�� ���� ����
		if (tempcontrow[i].length > max) {
			max = tempcontrow[i].length;
		}
	}

	for (int i = 0; tempcontrow[i + 1].length != 0; i++) {					//tempcontrow�� ����Ǿ� �ִ� ���� �� �߿��� ��ĭ�����ؼ� max�� �� ����
		if (tempcontrow[i].endx == tempcontrow[i + 1].endx && tempcontrow[i].endy + 2 == tempcontrow[i + 1].starty && tempcontrow[i].color == tempcontrow[i + 1].color && (board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 0 || board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 5))
			if (tempcontrow[i].length + tempcontrow[i + 1].length > max)
				max = tempcontrow[i].length + tempcontrow[i + 1].length;
	}












	//������
	contStone tempcontcol[tempSize] = { 0 };
	tempindex = 0;
	temp = 1;

	for (int i = 0; i < size; i++) {			//��, ������ ��� ���� ��ü �����ٿ��� 1�� �̻� ������ ���� ������ ����
		for (int j = 0; j < size - 1; j++) {
			switch (board[j][i]) {
			case 0:
			case 5:
				if (j == size - 2) {
					if (board[j + 1][i] == 1 || board[j + 1][i] == 3) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 1;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[j + 1][i] == 2 || board[j + 1][i] == 4) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 2;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][i] == 1 || board[j + 1][i] == 3) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 1;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontcol[tempindex].startx = j - temp + 1;
					tempcontcol[tempindex].starty = i;
					tempcontcol[tempindex].endx = j;
					tempcontcol[tempindex].endy = i;
					tempcontcol[tempindex].color = 1;
					tempcontcol[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[j + 1][i] == 2 || board[j + 1][i] == 4) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 2;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontcol[tempindex].startx = j - temp + 1;
					tempcontcol[tempindex].starty = i;
					tempcontcol[tempindex].endx = j;
					tempcontcol[tempindex].endy = i;
					tempcontcol[tempindex].color = 2;
					tempcontcol[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontcol[i].length != 0; i++) {						//tempcontcol�� ����Ǿ� �ִ� ���ӵ� �߿��� length�� max�� ���� ����
		if (tempcontcol[i].length > max) {
			max = tempcontcol[i].length;
		}
	}

	for (int i = 0; tempcontcol[i + 1].length != 0; i++) {					//tempcontcol�� ����Ǿ� �ִ� ���� �� �߿��� ��ĭ�����ؼ� max�� �� ����
		if (tempcontcol[i].endy == tempcontcol[i + 1].endy && tempcontcol[i].endx + 2 == tempcontcol[i + 1].startx && tempcontcol[i].color == tempcontcol[i + 1].color && (board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 0 || board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 5))
			if (tempcontcol[i].length + tempcontcol[i + 1].length > max)
				max = tempcontcol[i].length + tempcontcol[i + 1].length;
	}




	//�밢��1
	contStone tempcontdiag1[tempSize] = { 0 };
	tempindex = 0;

	temp = 1;

	for (int i = 0; i < size; i++) {			//��, ������ ��� ���� ��1 �밢������ 1�� �̻� ������ ���� ������ ����
		for (int j = 0; j < i; j++) {
			switch (board[size - 1 - i + j][j]) {
			case 0:
			case 5:
				if (j == i - 1) {
					if (board[size - 1 - i + j + 1][j + 1] == 1 || board[size - 1 - i + j + 1][j + 1] == 3) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 1;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[size - 1 - i + j + 1][j + 1] == 2 || board[size - 1 - i + j + 1][j + 1] == 4) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 2;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[size - i + j][j + 1] == 1 || board[size - i + j][j + 1] == 3) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 1;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 1;
					tempcontdiag1[tempindex].starty = j - temp + 1;
					tempcontdiag1[tempindex].endx = size - 1 - i + j;
					tempcontdiag1[tempindex].endy = j;
					tempcontdiag1[tempindex].color = 1;
					tempcontdiag1[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[size - i + j][j + 1] == 2 || board[size - i + j][j + 1] == 4) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 2;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 1;
					tempcontdiag1[tempindex].starty = j - temp + 1;
					tempcontdiag1[tempindex].endx = size - 1 - i + j;
					tempcontdiag1[tempindex].endy = j;
					tempcontdiag1[tempindex].color = 2;
					tempcontdiag1[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontdiag1[i].length != 0; i++) {						//tempcontdiag1�� ����Ǿ� �ִ� ���ӵ� �߿��� length�� max�� ���� ����
		if (tempcontdiag1[i].length > max) {
			max = tempcontdiag1[i].length;
		}
	}

	for (int i = 0; tempcontdiag1[i + 1].length != 0; i++) {					//tempcontdiag1�� ����Ǿ� �ִ� ���� �� �߿��� ��ĭ�����ؼ� max�� �� ����
		if (tempcontdiag1[i].endx + 2 == tempcontdiag1[i + 1].startx && tempcontdiag1[i].endy + 2 == tempcontdiag1[i + 1].starty && tempcontdiag1[i].color == tempcontdiag1[i + 1].color && (board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 0 || board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 5))
			if (tempcontdiag1[i].length + tempcontdiag1[i + 1].length > max)
				max = tempcontdiag1[i].length + tempcontdiag1[i + 1].length;
	}


	//�밢��2
	contStone tempcontdiag2[tempSize] = { 0 };
	tempindex = 0;

	temp = 1;

	for (int i = 1; i < size; i++) {			//��, ������ ��� ���� ��2 �밢������ 1�� �̻� ������ ���� ������ ����
		for (int j = 0; j < size - 1 - i; j++) {
			switch (board[j][j + i]) {
			case 0:
			case 5:
				if (j == size - 2 - i) {
					if (board[j + 1][j + i + 1] == 1 || board[j + 1][j + i + 1] == 3) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j + 1;
						tempcontdiag2[tempindex].endy = j + i + 1;
						tempcontdiag2[tempindex].color = 1;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[j + 1][j + i + 1] == 2 || board[j + 1][j + i + 1] == 4) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j + 1;
						tempcontdiag2[tempindex].endy = j + i + 1;
						tempcontdiag2[tempindex].color = 2;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][j + i + 1] == 1 || board[j + 1][j + i + 1] == 3) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j + 1;
						tempcontdiag2[tempindex].endy = j + i + 1;
						tempcontdiag2[tempindex].color = 1;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag2[tempindex].startx = j - temp + 1;
					tempcontdiag2[tempindex].starty = j + i - temp + 1;
					tempcontdiag2[tempindex].endx = j;
					tempcontdiag2[tempindex].endy = j + i;
					tempcontdiag2[tempindex].color = 1;
					tempcontdiag2[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[j + 1][j + i + 1] == 2 || board[j + 1][j + i + 1] == 4) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j + 1;
						tempcontdiag2[tempindex].endy = j + i + 1;
						tempcontdiag2[tempindex].color = 2;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag2[tempindex].startx = j - temp + 1;
					tempcontdiag2[tempindex].starty = j + i - temp + 1;
					tempcontdiag2[tempindex].endx = j;
					tempcontdiag2[tempindex].endy = j + i;
					tempcontdiag2[tempindex].color = 2;
					tempcontdiag2[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontdiag2[i].length != 0; i++) {						//tempcontdiag2�� ����Ǿ� �ִ� ���ӵ� �߿��� length�� max�� ���� ����
		if (tempcontdiag2[i].length > max) {
			max = tempcontdiag2[i].length;
		}
	}

	for (int i = 0; tempcontdiag2[i + 1].length != 0; i++) {					//tempcontdiag2�� ����Ǿ� �ִ� ���� �� �߿��� ��ĭ�����ؼ� max�� �� ����
		if (tempcontdiag2[i].endx + 2 == tempcontdiag2[i + 1].startx && tempcontdiag2[i].endy + 2 == tempcontdiag2[i + 1].starty && tempcontdiag2[i].color == tempcontdiag2[i + 1].color && (board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 0 || board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 5))
			if (tempcontdiag2[i].length + tempcontdiag2[i + 1].length > max)
				max = tempcontdiag2[i].length + tempcontdiag2[i + 1].length;
	}



	//�밢��3
	contStone tempcontdiag3[tempSize] = { 0 };
	tempindex = 0;

	temp = 1;

	for (int i = 0; i < size; i++) {			//��, ������ ��� ���� ��1 �밢������ 1�� �̻� ������ ���� ������ ����
		for (int j = 0; j < i; j++) {
			switch (board[j][i - j]) {
			case 0:
			case 5:
				if (j == i - 1) {
					if (board[j + 1][i - j - 1] == 1 || board[j + 1][i - j - 1] == 3) {
						tempcontdiag3[tempindex].startx = j - temp + 2;
						tempcontdiag3[tempindex].starty = i - j + temp - 2;
						tempcontdiag3[tempindex].endx = j + 1;
						tempcontdiag3[tempindex].endy = i - j - 1;
						tempcontdiag3[tempindex].color = 1;
						tempcontdiag3[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[j + 1][i - j - 1] == 2 || board[j + 1][i - j - 1] == 4) {
						tempcontdiag3[tempindex].startx = j - temp + 2;
						tempcontdiag3[tempindex].starty = i - j + temp - 2;
						tempcontdiag3[tempindex].endx = j + 1;
						tempcontdiag3[tempindex].endy = i - j - 1;
						tempcontdiag3[tempindex].color = 2;
						tempcontdiag3[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][i - j - 1] == 1 || board[j + 1][i - j - 1] == 3) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag3[tempindex].startx = j - temp + 2;
						tempcontdiag3[tempindex].starty = i - j + temp - 2;
						tempcontdiag3[tempindex].endx = j + 1;
						tempcontdiag3[tempindex].endy = i - j - 1;
						tempcontdiag3[tempindex].color = 1;
						tempcontdiag3[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag3[tempindex].startx = j - temp + 1;
					tempcontdiag3[tempindex].starty = i - j + temp - 1;
					tempcontdiag3[tempindex].endx = j;
					tempcontdiag3[tempindex].endy = i - j;
					tempcontdiag3[tempindex].color = 1;
					tempcontdiag3[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[j + 1][i - j - 1] == 2 || board[j + 1][i - j - 1] == 4) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag3[tempindex].startx = j - temp + 2;
						tempcontdiag3[tempindex].starty = i - j + temp - 2;
						tempcontdiag3[tempindex].endx = j + 1;
						tempcontdiag3[tempindex].endy = i - j - 1;
						tempcontdiag3[tempindex].color = 2;
						tempcontdiag3[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag3[tempindex].startx = j - temp + 1;
					tempcontdiag3[tempindex].starty = i - j + temp - 1;
					tempcontdiag3[tempindex].endx = j;
					tempcontdiag3[tempindex].endy = i - j;
					tempcontdiag3[tempindex].color = 2;
					tempcontdiag3[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontdiag3[i].length != 0; i++) {						//tempcontdiag3�� ����Ǿ� �ִ� ���ӵ� �߿��� length�� max�� ���� ����
		if (tempcontdiag3[i].length > max) {
			max = tempcontdiag3[i].length;
		}
	}

	for (int i = 0; tempcontdiag3[i + 1].length != 0; i++) {					//tempcontdiag3�� ����Ǿ� �ִ� ���� �� �߿��� ��ĭ�����ؼ� max�� �� ����
		if (tempcontdiag3[i].endx + 2 == tempcontdiag3[i + 1].startx && tempcontdiag3[i].endy - 2 == tempcontdiag3[i + 1].starty && tempcontdiag3[i].color == tempcontdiag3[i + 1].color && (board[tempcontdiag3[i].endx + 1][tempcontdiag3[i].endy - 1] == 0 || board[tempcontdiag3[i].endx + 1][tempcontdiag3[i].endy - 1] == 5))
			if (tempcontdiag3[i].length + tempcontdiag3[i + 1].length > max)
				max = tempcontdiag3[i].length + tempcontdiag3[i + 1].length;
	}



	//�밢�� 4
	contStone tempcontdiag4[tempSize] = { 0 };
	tempindex = 0;

	temp = 1;

	for (int i = 1; i < size; i++) {			//��, ������ ��� ���� ��2 �밢������ 1�� �̻� ������ ���� ������ ����
		for (int j = 0; j < size - 1 - i; j++) {
			switch (board[i + j][size - 1 - j]) {
			case 0:
			case 5:
				if (j == size - 2 - i) {
					if (board[i + j + 1][size - 2 - j] == 1 || board[i + j + 1][size - 2 - j] == 3) {
						tempcontdiag4[tempindex].startx = i + j - temp + 2;
						tempcontdiag4[tempindex].starty = size - 1 - j + temp - 2;
						tempcontdiag4[tempindex].endx = i + j + 1;
						tempcontdiag4[tempindex].endy = size - 1 - j - 1;
						tempcontdiag4[tempindex].color = 1;
						tempcontdiag4[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[i + j + 1][size - 2 - j] == 2 || board[i + j + 1][size - 2 - j] == 4) {
						tempcontdiag4[tempindex].startx = i + j - temp + 2;
						tempcontdiag4[tempindex].starty = size - 1 - j + temp - 2;
						tempcontdiag4[tempindex].endx = i + j + 1;
						tempcontdiag4[tempindex].endy = size - 1 - j - 1;
						tempcontdiag4[tempindex].color = 2;
						tempcontdiag4[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[i + j + 1][size - 2 - j] == 1 || board[i + j + 1][size - 2 - j] == 3) {
					temp++;
					if (j == size - 2 - i && temp != 1) {
						tempcontdiag4[tempindex].startx = i + j - temp + 2;
						tempcontdiag4[tempindex].starty = size - 1 - j + temp - 2;
						tempcontdiag4[tempindex].endx = i + j + 1;
						tempcontdiag4[tempindex].endy = size - 1 - j - 1;
						tempcontdiag4[tempindex].color = 1;
						tempcontdiag4[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag4[tempindex].startx = i + j - temp + 1;
					tempcontdiag4[tempindex].starty = size - 1 - j + temp - 1;
					tempcontdiag4[tempindex].endx = i + j;
					tempcontdiag4[tempindex].endy = size - 1 - j;
					tempcontdiag4[tempindex].color = 1;
					tempcontdiag4[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[i + j + 1][size - 2 - j] == 2 || board[i + j + 1][size - 2 - j] == 4) {
					temp++;
					if (j == size - 2 - i && temp != 1) {
						tempcontdiag4[tempindex].startx = i + j - temp + 2;
						tempcontdiag4[tempindex].starty = size - 1 - j + temp - 2;
						tempcontdiag4[tempindex].endx = i + j + 1;
						tempcontdiag4[tempindex].endy = size - 1 - j - 1;
						tempcontdiag4[tempindex].color = 2;
						tempcontdiag4[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag4[tempindex].startx = i + j - temp + 1;
					tempcontdiag4[tempindex].starty = size - 1 - j + temp - 1;
					tempcontdiag4[tempindex].endx = i + j;
					tempcontdiag4[tempindex].endy = size - 1 - j;
					tempcontdiag4[tempindex].color = 2;
					tempcontdiag4[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontdiag4[i].length != 0; i++) {						//tempcontdiag4�� ����Ǿ� �ִ� ���ӵ� �߿��� length�� max�� ���� ����
		if (tempcontdiag4[i].length > max) {
			max = tempcontdiag4[i].length;
		}
	}

	for (int i = 0; tempcontdiag4[i + 1].length != 0; i++) {					//tempcontdiag4�� ����Ǿ� �ִ� ���� �� �߿��� ��ĭ�����ؼ� max�� �� ����
		if (tempcontdiag4[i].endx + 2 == tempcontdiag4[i + 1].startx && tempcontdiag4[i].endy - 2 == tempcontdiag4[i + 1].starty && tempcontdiag4[i].color == tempcontdiag4[i + 1].color && (board[tempcontdiag4[i].endx + 1][tempcontdiag4[i].endy - 1] == 0 || board[tempcontdiag4[i].endx + 1][tempcontdiag4[i].endy - 1] == 5))
			if (tempcontdiag4[i].length + tempcontdiag4[i + 1].length > max)
				max = tempcontdiag4[i].length + tempcontdiag4[i + 1].length;
	}







	switch (option) {
	case 1: {
		if (max > 1) {
			for (int i = 0; tempcontrow[i].length != 0; i++) {						//tempcontrow�� ����Ǿ� �ִ� ���� �� �߿��� length�� max�� �����Ϳ� ��ĭ�����ؼ� max�� ������ ����
				if (tempcontrow[i].length == max) {
					Stonedata[dataindex++] = tempcontrow[i];
				}
				else if (tempcontrow[i + 1].length == 0)
					break;
				else if (tempcontrow[i].endx == tempcontrow[i + 1].endx && tempcontrow[i].endy + 2 == tempcontrow[i + 1].starty && tempcontrow[i].color == tempcontrow[i + 1].color && (board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 0 || board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 5) && tempcontrow[i].length + tempcontrow[i + 1].length == max) {
					Stonedata[dataindex].startx = tempcontrow[i].startx;
					Stonedata[dataindex].starty = tempcontrow[i].starty;
					Stonedata[dataindex].endx = tempcontrow[i].endx;
					Stonedata[dataindex].endy = tempcontrow[i + 1].endy;
					Stonedata[dataindex].color = tempcontrow[i].color;
					Stonedata[dataindex].length = tempcontrow[i].length + tempcontrow[i + 1].length;
					Stonedata[dataindex++].isempty = 1;
				}
			}
		}

		if (max > 1) {
			for (int i = 0; tempcontcol[i].length != 0; i++) {						//tempcontcol�� ����Ǿ� �ִ� ���� �� �߿��� length�� max�� �����Ϳ� ��ĭ�����ؼ� max�� ������ ����
				if (tempcontcol[i].length == max) {
					Stonedata[dataindex++] = tempcontcol[i];
				}
				else if (tempcontcol[i + 1].length == 0)
					break;
				else if (tempcontcol[i].endy == tempcontcol[i + 1].endy && tempcontcol[i].endx + 2 == tempcontcol[i + 1].startx && tempcontcol[i].color == tempcontcol[i + 1].color && (board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 0 || board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 5) && tempcontcol[i].length + tempcontcol[i + 1].length == max) {
					Stonedata[dataindex].startx = tempcontcol[i].startx;
					Stonedata[dataindex].starty = tempcontcol[i].starty;
					Stonedata[dataindex].endx = tempcontcol[i + 1].endx;
					Stonedata[dataindex].endy = tempcontcol[i].endy;
					Stonedata[dataindex].color = tempcontcol[i].color;
					Stonedata[dataindex].length = tempcontcol[i].length + tempcontcol[i + 1].length;
					Stonedata[dataindex++].isempty = 1;
				}
			}
		}

		if (max > 1) {
			for (int i = 0; tempcontdiag1[i].length != 0; i++) {						//tempcontdiag1�� ����Ǿ� �ִ� ���� �� �߿��� length�� max�� �����Ϳ� ��ĭ�����ؼ� max�� ������ ����
				if (tempcontdiag1[i].length == max) {
					Stonedata[dataindex++] = tempcontdiag1[i];
				}
				else if (tempcontdiag1[i + 1].length == 0)
					break;
				else if (tempcontdiag1[i].endx + 2 == tempcontdiag1[i + 1].startx && tempcontdiag1[i].endy + 2 == tempcontdiag1[i + 1].starty && tempcontdiag1[i].color == tempcontdiag1[i + 1].color && (board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 0 || board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 5) && tempcontdiag1[i].length + tempcontdiag1[i + 1].length == max) {
					Stonedata[dataindex].startx = tempcontdiag1[i].startx;
					Stonedata[dataindex].starty = tempcontdiag1[i].starty;
					Stonedata[dataindex].endx = tempcontdiag1[i + 1].endx;
					Stonedata[dataindex].endy = tempcontdiag1[i + 1].endy;
					Stonedata[dataindex].color = tempcontdiag1[i].color;
					Stonedata[dataindex].length = tempcontdiag1[i].length + tempcontdiag1[i + 1].length;
					Stonedata[dataindex++].isempty = 1;
				}
			}
		}

		if (max > 1) {
			for (int i = 0; tempcontdiag2[i].length != 0; i++) {						//tempcontdiag2�� ����Ǿ� �ִ� ���� �� �߿��� length�� max�� �����Ϳ� ��ĭ�����ؼ� max�� ������ ����
				if (tempcontdiag2[i].length == max) {
					Stonedata[dataindex++] = tempcontdiag2[i];
				}
				else if (tempcontdiag2[i + 1].length == 0)
					break;
				else if (tempcontdiag2[i].endx + 2 == tempcontdiag2[i + 1].startx && tempcontdiag2[i].endy + 2 == tempcontdiag2[i + 1].starty && tempcontdiag2[i].color == tempcontdiag2[i + 1].color && (board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 0 || board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 5) && tempcontdiag2[i].length + tempcontdiag2[i + 1].length == max) {
					Stonedata[dataindex].startx = tempcontdiag2[i].startx;
					Stonedata[dataindex].starty = tempcontdiag2[i].starty;
					Stonedata[dataindex].endx = tempcontdiag2[i + 1].endx;
					Stonedata[dataindex].endy = tempcontdiag2[i + 1].endy;
					Stonedata[dataindex].color = tempcontdiag2[i].color;
					Stonedata[dataindex].length = tempcontdiag2[i].length + tempcontdiag2[i + 1].length;
					Stonedata[dataindex++].isempty = 1;
				}
			}
		}

		if (max > 1) {
			for (int i = 0; tempcontdiag3[i].length != 0; i++) {						//tempcontdiag3�� ����Ǿ� �ִ� ���� �� �߿��� length�� max�� �����Ϳ� ��ĭ�����ؼ� max�� ������ ����
				if (tempcontdiag3[i].length == max) {
					Stonedata[dataindex++] = tempcontdiag3[i];
				}
				else if (tempcontdiag3[i + 1].length == 0)
					break;
				else if (tempcontdiag3[i].endx + 2 == tempcontdiag3[i + 1].startx && tempcontdiag3[i].endy - 2 == tempcontdiag3[i + 1].starty && tempcontdiag3[i].color == tempcontdiag3[i + 1].color && (board[tempcontdiag3[i].endx + 1][tempcontdiag3[i].endy - 1] == 0 || board[tempcontdiag3[i].endx + 1][tempcontdiag3[i].endy - 1] == 5) && tempcontdiag3[i].length + tempcontdiag3[i + 1].length == max) {
					Stonedata[dataindex].startx = tempcontdiag3[i].startx;
					Stonedata[dataindex].starty = tempcontdiag3[i].starty;
					Stonedata[dataindex].endx = tempcontdiag3[i + 1].endx;
					Stonedata[dataindex].endy = tempcontdiag3[i + 1].endy;
					Stonedata[dataindex].color = tempcontdiag3[i].color;
					Stonedata[dataindex].length = tempcontdiag3[i].length + tempcontdiag3[i + 1].length;
					Stonedata[dataindex++].isempty = 1;
				}
			}
		}

		if (max > 1) {
			for (int i = 0; tempcontdiag4[i].length != 0; i++) {						//tempcontdiag4�� ����Ǿ� �ִ� ���� �� �߿��� length�� max�� �����Ϳ� ��ĭ�����ؼ� max�� ������ ����
				if (tempcontdiag4[i].length == max) {
					Stonedata[dataindex++] = tempcontdiag4[i];
				}
				else if (tempcontdiag4[i + 1].length == 0)
					break;
				else if (tempcontdiag4[i].endx + 2 == tempcontdiag4[i + 1].startx && tempcontdiag4[i].endy - 2 == tempcontdiag4[i + 1].starty && tempcontdiag4[i].color == tempcontdiag4[i + 1].color && (board[tempcontdiag4[i].endx + 1][tempcontdiag4[i].endy - 1] == 0 || board[tempcontdiag4[i].endx + 1][tempcontdiag4[i].endy - 1] == 5) && tempcontdiag4[i].length + tempcontdiag4[i + 1].length == max) {
					Stonedata[dataindex].startx = tempcontdiag4[i].startx;
					Stonedata[dataindex].starty = tempcontdiag4[i].starty;
					Stonedata[dataindex].endx = tempcontdiag4[i + 1].endx;
					Stonedata[dataindex].endy = tempcontdiag4[i + 1].endy;
					Stonedata[dataindex].color = tempcontdiag4[i].color;
					Stonedata[dataindex].length = tempcontdiag4[i].length + tempcontdiag4[i + 1].length;
					Stonedata[dataindex++].isempty = 1;
				}
			}
		}

		return Stonedata;
	}
		  break;

	case 2: {
		// tempcontrow�� 3�Ǵ� 4�� length �߰�
		for (int i = 0; tempcontrow[i].length != 0; i++) {
			if (tempcontrow[i].length == 3 || tempcontrow[i].length == 4)
				Stonedata[dataindex++] = tempcontrow[i];
		}
		for (int i = 0; tempcontrow[i + 1].length != 0; i++) {
			if (tempcontrow[i].endx == tempcontrow[i + 1].endx && tempcontrow[i].endy + 2 == tempcontrow[i + 1].starty && tempcontrow[i].color == tempcontrow[i + 1].color && (board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 0 || board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 5) && (tempcontrow[i].length + tempcontrow[i + 1].length == 3 || tempcontrow[i].length + tempcontrow[i + 1].length == 4)) {
				contStone add = { 0 };
					add.startx = tempcontrow[i].startx;
					add.starty = tempcontrow[i].starty;
					add.endx = tempcontrow[i].endx;
					add.endy = tempcontrow[i + 1].endy;
					add.color = tempcontrow[i].color;
					add.length = tempcontrow[i].length + tempcontrow[i + 1].length;
					add.isempty = 1;

					Stonedata[dataindex++] = add;
			}
		}

		//tempcontcol
		for (int i = 0; tempcontcol[i].length != 0; i++) {
			if (tempcontcol[i].length == 3 || tempcontcol[i].length == 4)
				Stonedata[dataindex++] = tempcontcol[i];
		}
		for (int i = 0; tempcontcol[i + 1].length != 0; i++) {
			if (tempcontcol[i].endy == tempcontcol[i + 1].endy && tempcontcol[i].endx + 2 == tempcontcol[i + 1].startx && tempcontcol[i].color == tempcontcol[i + 1].color && (board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 0 || board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 5) && (tempcontcol[i].length + tempcontcol[i + 1].length == 3 || tempcontcol[i].length + tempcontcol[i + 1].length == 4)) {
				contStone add = { 0 };
				add.startx = tempcontcol[i].startx;
				add.starty = tempcontcol[i].starty;
				add.endx = tempcontcol[i + 1].endx;
				add.endy = tempcontcol[i].endy;
				add.color = tempcontcol[i].color;
				add.length = tempcontcol[i].length + tempcontcol[i + 1].length;
				add.isempty = 1;

				Stonedata[dataindex++] = add;
			}
		}

		//tempcontdiag1
		for (int i = 0; tempcontdiag1[i].length != 0; i++) {
			if (tempcontdiag1[i].length == 3 || tempcontdiag1[i].length == 4)
				Stonedata[dataindex++] = tempcontdiag1[i];
		}
		for (int i = 0; tempcontdiag1[i + 1].length != 0; i++) {
			if (tempcontdiag1[i].endx + 2 == tempcontdiag1[i + 1].startx && tempcontdiag1[i].endy + 2 == tempcontdiag1[i + 1].starty && tempcontdiag1[i].color == tempcontdiag1[i + 1].color && (board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 0 || board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 5) && (tempcontdiag1[i].length + tempcontdiag1[i + 1].length == 3 || tempcontdiag1[i].length + tempcontdiag1[i + 1].length == 4)) {
				contStone add = { 0 };
				add.startx = tempcontdiag1[i].startx;
				add.starty = tempcontdiag1[i].starty;
				add.endx = tempcontdiag1[i + 1].endx;
				add.endy = tempcontdiag1[i + 1].endy;
				add.color = tempcontdiag1[i].color;
				add.length = tempcontdiag1[i].length + tempcontdiag1[i + 1].length;
				add.isempty = 1;

				Stonedata[dataindex++] = add;
			}
		}

		//tempcontdiag2
		for (int i = 0; tempcontdiag2[i].length != 0; i++) {
			if (tempcontdiag2[i].length == 3 || tempcontdiag2[i].length == 4)
				Stonedata[dataindex++] = tempcontdiag2[i];
		}
		for (int i = 0; tempcontdiag2[i + 1].length != 0; i++) {
			if (tempcontdiag2[i].endx + 2 == tempcontdiag2[i + 1].startx && tempcontdiag2[i].endy + 2 == tempcontdiag2[i + 1].starty && tempcontdiag2[i].color == tempcontdiag2[i + 1].color && (board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 0 || board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 5) && (tempcontdiag2[i].length + tempcontdiag2[i + 1].length == 3 || tempcontdiag2[i].length + tempcontdiag2[i + 1].length == 4)) {
				contStone add = { 0 };
				add.startx = tempcontdiag2[i].startx;
				add.starty = tempcontdiag2[i].starty;
				add.endx = tempcontdiag2[i + 1].endx;
				add.endy = tempcontdiag2[i + 1].endy;
				add.color = tempcontdiag2[i].color;
				add.length = tempcontdiag2[i].length + tempcontdiag2[i + 1].length;
				add.isempty = 1;

				Stonedata[dataindex++] = add;
			}
		}

		//tempcontdiag3
		for (int i = 0; tempcontdiag3[i].length != 0; i++) {
			if (tempcontdiag3[i].length == 3 || tempcontdiag3[i].length == 4)
				Stonedata[dataindex++] = tempcontdiag3[i];
		}
		for (int i = 0; tempcontdiag3[i + 1].length != 0; i++) {
			if (tempcontdiag3[i].endx + 2 == tempcontdiag3[i + 1].startx && tempcontdiag3[i].endy - 2 == tempcontdiag3[i + 1].starty && tempcontdiag3[i].color == tempcontdiag3[i + 1].color && (board[tempcontdiag3[i].endx + 1][tempcontdiag3[i].endy - 1] == 0 || board[tempcontdiag3[i].endx + 1][tempcontdiag3[i].endy - 1] == 5) && (tempcontdiag3[i].length + tempcontdiag3[i + 1].length == 3 || tempcontdiag3[i].length + tempcontdiag3[i + 1].length == 4)) {
				contStone add = { 0 };
				add.startx = tempcontdiag3[i].startx;
				add.starty = tempcontdiag3[i].starty;
				add.endx = tempcontdiag3[i + 1].endx;
				add.endy = tempcontdiag3[i + 1].endy;
				add.color = tempcontdiag3[i].color;
				add.length = tempcontdiag3[i].length + tempcontdiag3[i + 1].length;
				add.isempty = 1;

				Stonedata[dataindex++] = add;
			}
		}

		//tempcontdiag4
		for (int i = 0; tempcontdiag4[i].length != 0; i++) {
			if (tempcontdiag4[i].length == 3 || tempcontdiag4[i].length == 4)
				Stonedata[dataindex++] = tempcontdiag4[i];
		}
		for (int i = 0; tempcontdiag4[i + 1].length != 0; i++) {
			if (tempcontdiag4[i].endx + 2 == tempcontdiag4[i + 1].startx && tempcontdiag4[i].endy - 2 == tempcontdiag4[i + 1].starty && tempcontdiag4[i].color == tempcontdiag4[i + 1].color && (board[tempcontdiag4[i].endx + 1][tempcontdiag4[i].endy - 1] == 0 || board[tempcontdiag4[i].endx + 1][tempcontdiag4[i].endy - 1] == 5) && (tempcontdiag4[i].length + tempcontdiag4[i + 1].length == 3 || tempcontdiag4[i].length + tempcontdiag4[i + 1].length == 4)) {
				contStone add = { 0 };
				add.startx = tempcontdiag4[i].startx;
				add.starty = tempcontdiag4[i].starty;
				add.endx = tempcontdiag4[i + 1].endx;
				add.endy = tempcontdiag4[i + 1].endy;
				add.color = tempcontdiag4[i].color;
				add.length = tempcontdiag4[i].length + tempcontdiag4[i + 1].length;
				add.isempty = 1;

				Stonedata[dataindex++] = add;
			}
		}

		return Stonedata;
	}
		  break;

	default:
		printf("\n\nERROR\n\n");
		exit(0);
	}
}

void changeStone(contStone* data)
{
	for (int i = 0; data[i].length != 0; i++) {
		int x = data[i].startx;
		int y = data[i].starty;



		int menu = 0;
		int reallen = data[i].length + data[i].isempty;
		int temp1 = (data[i].endx - data[i].startx) / (reallen - 1);
		int temp2 = (data[i].endy - data[i].starty) / (reallen - 1);

		if (temp1 == 0 && temp2 == 1)
			menu = 1;							//����
		else if (temp1 == 1 && temp2 == 0)
			menu = 2;							//����
		else if (temp1 == 1 && temp2 == 1)
			menu = 3;							//�ٴ밢��
		else if (temp1 == 1 && temp2 == -1)
			menu = 4;							//�״밢��


		switch (menu) {
		case 1:
			for (int j = 0; j < reallen; j++) {
				if (board[x][y + j] == 0)
					;
				else if (board[x][y + j] < 3)
					board[x][y + j] += 2;
			}
			break;

		case 2:
			for (int j = 0; j < reallen; j++) {
				if (board[x + j][y] == 0)
					;
				else if (board[x + j][y] < 3)
					board[x + j][y] += 2;
			}
			break;

		case 3:
			for (int j = 0; j < reallen; j++) {
				if (board[x + j][y + j] == 0)
					;
				else if (board[x + j][y + j] < 3)
					board[x + j][y + j] += 2;
			}
			break;

		case 4:
			for (int j = 0; j < reallen; j++) {
				if (board[x + j][y - j] == 0)
					;
				else if (board[x + j][y - j] < 3)
					board[x + j][y - j] += 2;
			}
			break;


		default:
			break;
		}



	}
}

void prtcontStone(contStone* data)
{
	printf("--------------------�ִ� ������ ��ǥ ���---------------------\n");
	for (int i = 0; data[i].length != 0; i++) {
		if (data[i].color == 1)
			printf("���� �� : ");
		else if (data[i].color == 2)
			printf("  �� �� : ");
		printf("( %2d, %2d ) ~ ( %2d, %2d )\n", data[i].startx, data[i].starty, data[i].endx, data[i].endy);
	}
	printf("\n");
}

void checkstop(contStone* data)
{
	for (int i = 0; data[i].length != 0; i++) {
		int menu = 0;
		int reallen = data[i].length + data[i].isempty;
		int temp1 = (data[i].endx - data[i].startx) / (reallen - 1);
		int temp2 = (data[i].endy - data[i].starty) / (reallen - 1);

		int colortemp = count % 2 + 1;

		if (temp1 == 0 && temp2 == 1)
			menu = 1;							//����
		else if (temp1 == 1 && temp2 == 0)
			menu = 2;							//����
		else if (temp1 == 1 && temp2 == 1)
			menu = 3;							//�ٴ밢��
		else if (temp1 == 1 && temp2 == -1)
			menu = 4;							//�״밢��


		switch (menu) {
		case 1:
			if (data[i].color == colortemp) {
				if (data[i].isempty) {
					for (int j = data[i].starty; j < reallen + data[i].starty; j++) {
						if (board[data[i].startx][j] == 0) {
							board[data[i].startx][j] = 5;
							break;
						}
					}
				}
				else {
					if (data[i].length == 3) {
						if (data[i].starty != 0 && data[i].endy != size - 1 && (board[data[i].startx][data[i].starty - 1] == 0 || board[data[i].startx][data[i].starty - 1] == 5) && (board[data[i].endx][data[i].endy + 1] == 0 || board[data[i].endx][data[i].endy + 1] == 5)) {
							board[data[i].startx][data[i].starty - 1] = 5;
							board[data[i].endx][data[i].endy + 1] = 5;
						}
					}
					else if (data[i].length == 4) {
						if (data[i].starty != 0 && board[data[i].startx][data[i].starty - 1] == 0)
							board[data[i].startx][data[i].starty - 1] = 5;
						if (data[i].endy != size - 1 && board[data[i].endx][data[i].endy + 1] == 0)
							board[data[i].endx][data[i].endy + 1] = 5;
					}
				}
			}
			break;
		case 2:
			if (data[i].color == colortemp) {
				if (data[i].isempty) {
					for (int j = data[i].startx; j < reallen + data[i].startx; j++) {
						if (board[j][data[i].starty] == 0) {
							board[j][data[i].starty] = 5;
							break;
						}
					}
				}
				else {
					if (data[i].length == 3) {
						if (data[i].startx != 0 && data[i].endx != size - 1 && (board[data[i].startx - 1][data[i].starty] == 0 || board[data[i].startx - 1][data[i].starty] == 5) && (board[data[i].endx + 1][data[i].endy] == 0 || board[data[i].endx + 1][data[i].endy] == 5)) {
							board[data[i].startx - 1][data[i].starty] = 5;
							board[data[i].endx + 1][data[i].endy] = 5;
						}
					}
					else if (data[i].length == 4) {
						if (data[i].startx != 0 && board[data[i].startx - 1][data[i].starty] == 0)
							board[data[i].startx - 1][data[i].starty] = 5;
						if (data[i].endx != size - 1 && board[data[i].endx + 1][data[i].endy] == 0)
							board[data[i].endx + 1][data[i].endy] = 5;
					}
				}
			}
			break;


		case 3:
			if (data[i].color == colortemp) {
				if (data[i].isempty) {
					for (int j = data[i].startx, k = data[i].starty; j < reallen + data[i].startx; j++, k++) {
						if (board[j][k] == 0) {
							board[j][k] = 5;
							break;
						}
					}
				}
				else {
					if (data[i].length == 3) {
						if (data[i].startx != 0 && data[i].starty != 0 && data[i].endx != size - 1 && data[i].endy != size - 1 && (board[data[i].startx - 1][data[i].starty - 1] == 0 || board[data[i].startx - 1][data[i].starty - 1] == 5) && (board[data[i].endx + 1][data[i].endy + 1] == 0 || board[data[i].endx + 1][data[i].endy + 1] == 5)) {
							board[data[i].startx - 1][data[i].starty - 1] = 5;
							board[data[i].endx + 1][data[i].endy + 1] = 5;
						}
					}
					else if (data[i].length == 4) {
						if (data[i].startx != 0 && data[i].starty != 0 && board[data[i].startx - 1][data[i].starty - 1] == 0)
							board[data[i].startx - 1][data[i].starty - 1] = 5;
						if (data[i].endx != size - 1 && data[i].endy != size - 1 && board[data[i].endx + 1][data[i].endy + 1] == 0)
							board[data[i].endx + 1][data[i].endy + 1] = 5;
					}
				}
			}
			break;

		case 4:
			if (data[i].color == colortemp) {
				if (data[i].isempty) {
					for (int j = data[i].startx, k = data[i].starty; j < reallen + data[i].startx; j++, k--) {
						if (board[j][k] == 0) {
							board[j][k] = 5;
							break;
						}
					}
				}
				else {
					if (data[i].length == 3) {
						if (data[i].startx != 0 && data[i].starty != size - 1 && data[i].endx != size - 1 && data[i].endy != 0 && (board[data[i].startx - 1][data[i].starty + 1] == 0 || board[data[i].startx - 1][data[i].starty + 1] == 5) && (board[data[i].endx + 1][data[i].endy - 1] == 0 || board[data[i].endx + 1][data[i].endy - 1] == 5)) {
							board[data[i].startx - 1][data[i].starty + 1] = 5;
							board[data[i].endx + 1][data[i].endy - 1] = 5;
						}
					}
					else if (data[i].length == 4) {
						if (data[i].startx != 0 && data[i].starty != size - 1 && board[data[i].startx - 1][data[i].starty + 1] == 0)
							board[data[i].startx - 1][data[i].starty + 1] = 5;
						if (data[i].endx != size - 1 && data[i].endy != 0 && board[data[i].endx + 1][data[i].endy - 1] == 0)
							board[data[i].endx + 1][data[i].endy - 1] = 5;
					}
				}
			}
			break;


		default:
			break;
		}
	}

}

StoneStack Pop(StoneStack** sp)
{
	if (*sp == NULL) {
		StoneStack temp = { -1, -1, -1, NULL };
		return temp;
	}

	StoneStack value = **sp;
	value.next = NULL;

	StoneStack* temp = *sp;

	*sp = (*sp)->next;

	free(temp);

	return value;
}

void Push(StoneStack** sp, StoneStack data)
{
	StoneStack* temp = (StoneStack*)malloc(sizeof(StoneStack));
	*temp = data;

	temp->next = *sp;
	*sp = temp;
}

void Load(StoneStack** mainsp, StoneStack** undosp)
{
	FILE* temp = fopen("data.txt", "a");
	fclose(temp);
	temp = fopen("undo.txt", "a");
	fclose(temp);

	StoneStack* tempStack1 = NULL;
	StoneStack* tempStack2 = NULL;

	temp = fopen("data.txt", "r");
	while (!feof(temp)) {
		StoneStack value = { -1, -1, -1, NULL };
		if (fscanf(temp, "%d, %d, %d\n", &value.x, &value.y, &value.color) < 3)
			break;
		Push(&tempStack1, value);
		board[value.x][value.y] = value.color;
	}
	fclose(temp);


	temp = fopen("undo.txt", "r");
	while (!feof(temp)) {
		StoneStack value = { -1, -1, -1, NULL };
		if (fscanf(temp, "%d, %d, %d\n", &value.x, &value.y, &value.color) < 3)
			break;
		Push(&tempStack2, value);
	}
	fclose(temp);

	while (1) {
		StoneStack tempValue = Pop(&tempStack1);
		if (tempValue.x == -1)
			break;
		Push(mainsp, tempValue);
	}

	while (1) {
		StoneStack tempValue = Pop(&tempStack2);
		if (tempValue.x == -1)
			break;
		Push(undosp, tempValue);
	}
}

void Save(StoneStack* mainsp, StoneStack* undosp)
{
	FILE* temp = fopen("data.txt", "w");

	for (StoneStack* p = mainsp; p != NULL; p = p->next) {
		fprintf(temp, "%d, %d, %d\n", p->x, p->y, p->color);
	}
	fclose(temp);

	temp = fopen("undo.txt", "w");

	for (StoneStack* p = undosp; p != NULL; p = p->next) {
		fprintf(temp, "%d, %d, %d\n", p->x, p->y, p->color);
	}
	fclose(temp);
}

void Reset(StoneStack** sp)
{
	while (1) {
		StoneStack temp = Pop(sp);
		if (temp.x == -1)
			break;
	}
}


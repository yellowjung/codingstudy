#include <stdio.h>

#define MAX_TABLE (10007)
typedef unsigned long long int ull;

int N, M;
typedef struct st
{
	int index;
	char name[21];
	struct st *next;
}POKETMON;

POKETMON HASH_TABLE[MAX_TABLE];
POKETMON POOL[100000 + 5000];
int pcnt;

POKETMON ARR[100000 + 5000];

ull hash(const char *str)
{
	ull hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

void mystrcpy(char *a, const char *b)
{
	while (*a++ = *b++);
}

int mystrcmp(const char *a, const char *b)
{
	while (*a && *a == *b) ++a, ++b;
	return *a - *b;
}

int change(char *str)
{
	int i, len;
	int sum, mul;

	sum = 0;
	mul = 1;

	for (i = 0; str[i]; i++);
	len = i;

	for (i = len - 1; i >= 0; i--)
	{
		sum += (str[i] - '0') * mul;
		mul *= 10;
	}

	return sum;
}

int main(void)
{
	char str[21];

	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++)
	{
		scanf("%s", str);

		ull h = hash(str);
		POKETMON *nd = &POOL[pcnt++];

		nd->index = i;
		mystrcpy(nd->name, str);

		nd->next = HASH_TABLE[h].next;
		HASH_TABLE[h].next = nd; /* name에 해당하는 key에 연결 */

		mystrcpy(ARR[i].name, str); /* 순서대로 저장 */
	}

	for (int i = 0; i < M; i++)
	{
		scanf("%s", str);

		if ('0' < str[0] && str[0] <= '9')
		{
			int index = change(str);

			printf("%s\n", ARR[index].name); /* ARR에 순서대로 저장했기 때문에 그대로 출력 */
		}
		else
		{
			ull h = hash(str);
			POKETMON *nd = HASH_TABLE[h].next;

			while (nd)
			{
				if (!mystrcmp(nd->name, str))
				{
					printf("%d\n", nd->index);
					break;
				}

				nd = nd->next;
			}
		}
	}

	return 0;
}
#include <iostream>

using namespace std;

int N;

int minHeap[100100];
int minHn;

int maxHeap[100100];
int maxHn;

void maxPush(int* heap, int& hn, int x)
{
	register int tmp;

	heap[++hn] = x;

	for (register int i = hn; i > 1; i /= 2)
	{
		if (heap[i / 2] > heap[i]) break;

		tmp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = tmp;
	}
}

int maxPop(int* heap, int& hn)
{
	register int tmp, ret;

	ret = heap[1];
	heap[1] = heap[hn];
	heap[hn--] = -10001;

	for (register int i = 1; i * 2 <= hn;)
	{
		if (heap[i] > heap[i * 2] && heap[i] > heap[i * 2 + 1]) break;
		else if (heap[i * 2] > heap[i * 2 + 1])
		{
			tmp = heap[i * 2];
			heap[i * 2] = heap[i];
			heap[i] = tmp;

			i = i * 2;
		}
		else
		{
			tmp = heap[i * 2 + 1];
			heap[i * 2 + 1] = heap[i];
			heap[i] = tmp;

			i = i * 2 + 1;
		}
	}

	return ret;
}

int minPop(int* heap, int& hn)
{
	register int tmp, ret;

	ret = heap[1];
	heap[1] = heap[hn];
	heap[hn--] = 10001;

	for (register int i = 1; i * 2 <= hn;)
	{
		if (heap[i] < heap[i * 2] && heap[i] < heap[i * 2 + 1]) break;
		else if (heap[i * 2]< heap[i * 2 + 1])
		{
			tmp = heap[i * 2];
			heap[i * 2] = heap[i];
			heap[i] = tmp;

			i = i * 2;
		}
		else
		{
			tmp = heap[i * 2 + 1];
			heap[i * 2 + 1] = heap[i];
			heap[i] = tmp;

			i = i * 2 + 1;
		}
	}

	return ret;
}

void minPush(int* heap, int& hn, int x)
{
	register int tmp;

	heap[++hn] = x;

	for (register int i = hn; i > 1; i /= 2)
	{
		if (heap[i / 2] < heap[i]) break;

		tmp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = tmp;
	}
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int input;

    cin >> N;

    cin >> input;

    minPush(minHeap, minHn, input);

    cout << input << "\n";

    for(int i = 1; i < N; i++){
        cin >> input;
        if(maxHn == minHn){
            if(input < maxHeap[1]){
                minPush(minHeap, minHn, maxPop(maxHeap, maxHn));
                maxPush(maxHeap, maxHn, input);
                cout << minHeap[1] << "\n"; 
            }else{
                minPush(minHeap, minHn, input);
                cout << minHeap[1] << "\n";
            }
        }else{
            if(minHeap[1] < input){
                maxPush(maxHeap, maxHn, minPop(minHeap, minHn));
                minPush(minHeap, minHn, input);
                cout << maxHeap[1] <<"\n";
            }else{
                maxPush(maxHeap, maxHn, input);
                cout << maxHeap[1] <<"\n";
            }
        }
    }

    return 0;
}
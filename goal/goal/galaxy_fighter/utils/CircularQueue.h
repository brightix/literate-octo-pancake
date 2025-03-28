#pragma once
template<typename T,int N = 10>
class CircularQueue
{
	T arr[N];
	int head;
	int tail;
	int curSize;
	int capacity;
public:
	CircularQueue():head(-1),tail(0),curSize(0),capacity(N) {
	}
	void push(T val) {
		if (curSize < capacity) {
			curSize++;
		}
		head = (head + 1) % capacity;
		arr[head] = val;
	}
	void pop() {
		if (curSize == 0) {
			return;
		}
		tail = (tail + 1) % capacity;
		curSize--;
	}

	T front() {
		return arr[head];
	}
	T back() {
		return arr[tail];
	}
	int getHead() {
		return head;
	}
	int getTail() {
		return tail;
	}
	int size() {
		return curSize;
	}
	void clear() {
		head = -1, tail = 0, curSize = 0;
	}
	T& operator[](int i) {
		if (i < 0 || i >= curSize) {
			throw std::out_of_range("Index out of range");
		}
		return arr[(tail + i) % capacity];
	}
};


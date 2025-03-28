#include "pch.h"
#include "InputBuffer.h"

//using namespace std;
//void InputBuffer::registerInput(const string& key)
//{
//	Uint64 n = Timer::Instance().getTicks();
//	buffer.push({key,n});
//	while (buffer.size() > maxBufferSize) {
//		buffer.pop();
//	}
//	while (!buffer.empty() && n - buffer.front().second > maxTimeGap) {
//		buffer.pop();
//	}
//}
//
//bool InputBuffer::checkCombo(const vector<string>& combo)
//{
//	if(buffer.size() < combo.size())
//		return false;
//	vector<string> recent;
//	auto tmp = buffer;
//	while (!tmp.empty()) {
//		recent.push_back(tmp.front().first);
//		tmp.pop();
//	}
//	int start = recent.size() - combo.size();
//	for (int i = 0;i < combo.size();i++) {
//		if (recent[start + i] != combo[i])
//			return false;
//	}
//	return true;
//}



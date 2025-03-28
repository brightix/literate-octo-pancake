#include "pch.h"
#include "core/Timer.h"

using namespace std;

int main() {
	Timer& timer = Timer::Instance();
	while (true) {
		timer.update();
		//��������
		cout << timer.getRefreshTime() << endl;
		timer.sleep(timer.getRefreshTime());
	}
	return 0;
}
#pragma once
class Context
{
private:
	std::unordered_map<std::string, std::shared_ptr<void>> data;
public:
	void initData(const std::string& key, std::shared_ptr<void> value);

	template<typename T>
	void setData(const std::string& key, const T& newValue) {
		auto it = data.find(key);
		if (it != data.end()) {
			std::shared_ptr<T> ptr = std::static_pointer_cast<T>(it->second);
			if (ptr) {
				*ptr = newValue;
			}
		}
	}

	template<typename T>
	std::shared_ptr<T> getData(const std::string& key) {
		auto it = data.find(key);
		if (it != data.end()) {
			return std::static_pointer_cast<T>(it->second);
		}
		std::cout << "没有 " << key << "的数据" << std::endl;
		return nullptr;
	}
};


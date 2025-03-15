#include "pch.h"
#include "Context.h"

void Context::initData(const std::string& key, shared_ptr<void> value)
{
	data[key] = value;
}


#pragma once
#include <optional>
#include <any>

//prototype. Very close, but not working properly

class MyAny
{
	struct Base {
		virtual ~Base() {} ;
		virtual Base* getCopy() = 0;
	};

	template <class T>
	struct Derived : public Base {
		T value;

		Derived(const T& value) : value(value) {};
		Base* get_copy() {
			return new Derived<T>(value);
		}
	};

	Base* storage;

public:
	
	MyAny() : storage(nullptr) {};
	template <class U>
	explicit MyAny(const U& value) : storage(new Derived<U>(value)) {};
	MyAny(const MyAny& other) : storage(other.storage->getCopy()) {};
	MyAny(MyAny&& other) : storage(other.storage) {
		other.storage = nullptr;
	}
	template <class U>
	MyAny(U&& other) : storage(new Derived<U>(other)) {
		//??
	}
	template <class U>
	MyAny& operator=(const std::optional<U>& value)
	{
		if (value.has_value()) {
			delete storage;
			storage = new Derived<U>(value.value);
		}
	}
/*	const std::type_info& type() const noexcept {
		return std::type_info(dynamic_cast<D>)
	}*/
	~MyAny() {
		delete storage;
	}
/*	template <class U>
	U get() {
		Derived<U>* res = dynamic_cast<Derived<U>*>(storage);
		if (res != nullptr) return res->value;
	}
	*/

	template <class ValueType>
	friend ValueType my_any_cast(const MyAny& operand);
};

template <class ValueType>
ValueType my_any_cast(const MyAny& operand) {
	MyAny::Derived<ValueType>* res = dynamic_cast<MyAny::Derived<ValueType>*>(operand.storage);
	if (res != nullptr) return res->value;
}

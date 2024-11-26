#include "bigint.hpp"

bigint::bigint() : value("0") {}

bigint::bigint(const std::string &str) {
    if (str.empty() || !std::all_of(str.begin(), str.end(), ::isdigit)) {
        throw std::invalid_argument("Invalid number string");
    }
    value = str;
    remove_leading_zeros();
}

bigint::bigint(unsigned long long num) : value(std::to_string(num)) {}

bigint::bigint(const bigint &other) : value(other.value) {}

void bigint::remove_leading_zeros() {
    value.erase(0, value.find_first_not_of('0'));
    if (value.empty()) {
        value = "0";
    }
}

//------------------------------------------------------------------//

bool bigint::operator<(const bigint &other) const {
    if (value.size() != other.value.size()) {
        return value.size() < other.value.size();
    }
    return value < other.value; // Comparación lexicográfica.
	//return (other > *this);
}

bool bigint::operator>(const bigint &other) const {
    return value < other.value;
}

bool bigint::operator<=(const bigint &other) const {
    return (*this < other || *this == other);
}

bool bigint::operator>=(const bigint &other) const {
    return (*this > other || *this == other);
}

bool bigint::operator==(const bigint &other) const {
    return (value == other.value);
}

bool bigint::operator!=(const bigint &other) const {
    return !(*this == other);
}


bigint bigint::operator+(const bigint &other) const {
    std::string result;
    int carry = 0;

	std::string::const_reverse_iterator it1 = value.rbegin();
	std::string::const_reverse_iterator it2 = other.value.rbegin();
	
    while (it1 != value.rend() || it2 != other.value.rend() || carry) {
        int digit1 = (it1 != value.rend() ? *it1++ - '0' : 0);
        int digit2 = (it2 != other.value.rend() ? *it2++ - '0' : 0);

        int sum = digit1 + digit2 + carry;
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return bigint(result);
}

bigint bigint::operator-(const bigint &other) const {
	if (*this < other) {
		throw std::invalid_argument("Negative result");
	}
	return bigint(0);
}

bigint& bigint::operator+=(const bigint &other) {
    *this = *this + other;
    return *this;
}

bigint bigint::operator<<(size_t shift) const {
    return bigint(value + std::string(shift, '0'));
}

bigint& bigint::operator<<=(size_t shift) {
    value += std::string(shift, '0');
    return *this;
}

bigint bigint::operator>>(size_t shift) const {
    if (shift >= value.size()) {
        return bigint(0);
    }
    return bigint(value.substr(0, value.size() - shift));
}

bigint& bigint::operator>>=(size_t shift) {
    if (shift >= value.size()) {
        value = "0";
    } else {
        value = value.substr(0, value.size() - shift);
    }
    return *this;
}

bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp = *this;
    ++(*this);
    return temp;
}

std::ostream& operator<<(std::ostream &os, const bigint &num) {
    os << num.value;
    return os;
}

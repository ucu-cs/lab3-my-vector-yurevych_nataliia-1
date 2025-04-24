#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <memory>
#include <cmath>


template<typename T>
class my_vector {
    static constexpr size_t MIN_VECTOR_LEN = 2;
    static constexpr size_t SIZE_MULT = 2;

private:
    T *data_m;
    size_t size_m;
    size_t capacity_m;

    class my_iterator {
    private:
        T *ptr_m;

    public:
        // used as reference: https://stackoverflow.com/questions/12092448/code-for-a-basic-random-access-iterator-based-on-pointers
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        my_iterator() : ptr_m(nullptr) {
        }

        my_iterator(T *rhs) : ptr_m(rhs) {
        }

        my_iterator(const my_iterator &rhs) : ptr_m(rhs.ptr_m) {
        }

        /* inline my_iterator& operator=(Type* rhs) {_ptr = rhs; return *this;} */
        /* inline my_iterator& operator=(const my_iterator &rhs) {_ptr = rhs._ptr; return *this;} */
        my_iterator &operator+=(difference_type rhs) {
            ptr_m += rhs;
            return *this;
        }

        my_iterator &operator-=(difference_type rhs) {
            ptr_m -= rhs;
            return *this;
        }

        T &operator*() const { return *ptr_m; }
        T *operator->() const { return ptr_m; }
        T &operator[](difference_type rhs) const { return ptr_m[rhs]; }

        my_iterator &operator++() {
            ++ptr_m;
            return *this;
        }

        my_iterator &operator--() {
            --ptr_m;
            return *this;
        }

        my_iterator operator++(int) const {
            my_iterator tmp(*this);
            ++ptr_m;
            return tmp;
        }

        my_iterator operator--(int) const {
            my_iterator tmp(*this);
            --ptr_m;
            return tmp;
        }

        /* inline my_iterator operator+(const my_iterator& rhs) {return my_iterator(_ptr+rhs.ptr);} */
        difference_type operator-(const my_iterator &rhs) const { return ptr_m - rhs.ptr_m; }
        my_iterator operator+(difference_type rhs) const { return my_iterator(ptr_m + rhs); }
        my_iterator operator-(difference_type rhs) const { return my_iterator(ptr_m - rhs); }

        friend my_iterator operator+(difference_type lhs, const my_iterator &rhs) {
            return my_iterator(lhs + rhs.ptr_m);
        }

        friend my_iterator operator-(difference_type lhs, const my_iterator &rhs) {
            return my_iterator(lhs - rhs.ptr_m);
        }

        bool operator==(const my_iterator &rhs) const { return ptr_m == rhs.ptr_m; }
        bool operator!=(const my_iterator &rhs) const { return ptr_m != rhs.ptr_m; }
        bool operator>(const my_iterator &rhs) const { return ptr_m > rhs.ptr_m; }
        bool operator<(const my_iterator &rhs) const { return ptr_m < rhs.ptr_m; }
        bool operator>=(const my_iterator &rhs) const { return ptr_m >= rhs.ptr_m; }
        bool operator<=(const my_iterator &rhs) const { return ptr_m <= rhs.ptr_m; }
    };

public:
    using reference = T &;
    using const_reference = const T &;

    using iterator = my_iterator;
    using const_iterator = const iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Default constructor
    my_vector();

    // Constructor for a vector of a certain size
    my_vector(size_t size);

    // Constructor that creates a vector with N copies of an element
    my_vector(size_t size, const T &value);

    // Constructor that copies an interval set with Iterators
    template<class InputIt>
    my_vector(InputIt first, InputIt last);

    // Constructor from inizialization list
    my_vector(std::initializer_list<T> init);

    // Copy constructor
    my_vector(const my_vector<T> &other);

    // Move constructor
    my_vector(my_vector<T> &&other) noexcept;

    // Destructor
    ~my_vector();

    // is_empty()
    [[nodiscard]] bool is_empty() const;

    // size()
    size_t size();

    // Assign
    void assign(size_t count, const T &value);

    template<class InputIt>
    void assign(InputIt first, InputIt last);

    void assign(std::initializer_list<T> ilist);

    // Assignment
    my_vector &operator=(const my_vector &other);

    my_vector &operator=(std::initializer_list<T> ilist);

    // Assignment with moving
    my_vector &operator=(my_vector &&other) noexcept;

    // front()
    reference front();

    const_reference front() const;

    // back()
    reference back();

    const_reference back() const;

    // Iterators compatible with adapters from standard lib and methods for working with them
    // (begin(), end(), cbegin(), cend(), rbegin(), rend(), rcbegin(), rcend()

    // Begin / End
    iterator begin() { return iterator(&data_m[0]); }
    // const_iterator begin() const { return const_iterator(data_m[0]); }
    const_iterator cbegin() const noexcept { return const_iterator(&data_m[0]); }

    iterator end() { return iterator(&data_m[size_m]); }
    // const_iterator end() const { return iterator(data_m[size_m]); }
    const_iterator cend() const noexcept { return iterator(&data_m[size_m]); }

    // Reverse iterators
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    // Index query with no checks operator[]
    T &operator[](size_t index);

    // Method at() that throws exceptions
    const T &at(size_t index) const;

    T &operator[](size_t index) const;

    // resize()
    void resize(size_t new_size);

    void resize(size_t new_size, const T &new_element);

    // reserve()
    void reserve(size_t new_capacity);

    // capacity()
    [[nodiscard]] size_t capacity() const;

    // size()
    [[nodiscard]] size_t size() const;

    // shrink_to_fit()
    void shrink_to_fit();

    // swap()
    void swap(my_vector &other) noexcept;

    // clear()
    void clear();

    // Two types of insert() - the first one takes Iterator where to insert and a value,
    // the second takes iterator where to insert and a pair of iterators from where to take.
    // Returns an iterator to the first inserted element
    iterator insert(const_iterator pos, const T &value); // Iterator pointing to the inserted value.

    // iterator insert(const_iterator pos, T &&value); // Iterator pointing to the inserted value.
    // iterator insert(const_iterator pos,
    //                 size_type count,
    //                 const T &value);

    // Iterator pointing to the first element inserted, or pos if no element is inserted.

    template<class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);

    // Iterator pointing to the first element inserted, or pos if no element is inserted.
    // iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    // erase() two types - to delete one element and to delete an interval
    iterator erase(const_iterator pos);

    iterator erase(const_iterator first, const_iterator last);

    // pop_back()
    void pop_back();

    // push_back()
    void push_back(const T &value);

    void push_back(T &&value);

    // emplace_back()
    template<class... Args>
    reference emplace_back(Args &&... args);

    // template< class... Args >
    // iterator emplace( const_iterator pos, Args&&... args );
};


template<typename T>
my_vector<T>::my_vector() : data_m{nullptr}, size_m{0}, capacity_m{0} {
    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
}

template<typename T>
my_vector<T>::my_vector(const size_t size) : data_m{nullptr}, size_m{size}, capacity_m{size} {
    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size));
}

template<typename T>
my_vector<T>::my_vector(const size_t size, const T &value) : data_m{nullptr}, size_m{size}, capacity_m{0} {
    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size));

    for (size_t i = 0; i < size; i++) {
        data_m[i] = value;
    }
}

template<typename T>
template<class InputIt>
my_vector<T>::my_vector(InputIt first, InputIt last) : size_m(0), capacity_m(0), data_m(nullptr) {
    size_m = std::distance(first, last);
    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
    // capacity_m = size_m;

    for (size_t i = 0; first != last; ++first) {
        new(&data_m[i]) T{*first};
        ++i;
    }
}

template<typename T>
my_vector<T>::my_vector(std::initializer_list<T> init) : data_m(nullptr), size_m(init.size()), capacity_m(init.size()) {
    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));

    auto it = init.begin();
    for (size_t i = 0; i < init.size(); ++i, ++it) {
        data_m[i] = *it;
    }
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T> &other) {
    size_m = other.size_m;
    capacity_m = other.capacity_m;

    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));

    for (size_t i = 0; i < size_m; i++) {
        data_m[i] = other.data_m[i];
    }
}

template<typename T>
my_vector<T>::my_vector(my_vector<T> &&other) noexcept {
    data_m = std::move(other.data_m);
    size_m = other.size_m;
    capacity_m = other.capacity_m;

    // other.data_m = nullptr;
    // other.size_m = 0;
    // other.capacity_m = 0;
}

template<typename T>
my_vector<T>::~my_vector() {
    clear();

    ::operator delete(data_m);
}

template<typename T>
bool my_vector<T>::is_empty() const {
    return size_m == 0;
}

template<typename T>
size_t my_vector<T>::size() {
    return size_m;
}

template<typename T>
void my_vector<T>::assign(size_t count, const T &value) {
    if (size_m < count) {
        size_m = count;
        reserve(SIZE_MULT * size_m);
    }

    size_m = count;

    for (size_t i = 0; i < size_m; i++) {
        data_m[i] = value;
    }
}

template<typename T>
template<class InputIt>
void my_vector<T>::assign(InputIt first, InputIt last) {
    if (std::distance(first, last) > size_m) {
        size_m = std::distance(first, last);
        reserve(SIZE_MULT * size_m);
    }

    size_t i = 0;
    for (InputIt it = first; it != last; ++it) {
        data_m[i++] = *it;
    }
}

template<typename T>
void my_vector<T>::assign(std::initializer_list<T> ilist) {
    size_m = ilist.size();

    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));

    auto it = ilist.begin();
    for (size_t i = 0; i < size_m; ++i, ++it) {
        data_m[i] = *it;
    }
}

template<typename T>
typename my_vector<T>::iterator my_vector<T>::erase(const_iterator pos) {
    size_t index = pos - const_iterator(data_m);

    if (index >= size_m) {
        throw std::out_of_range("erase position out of range");
    }

    data_m[index].~T();

    for (size_t i = index; i < size_m - 1; ++i) {
        new(&data_m[i]) T(std::move(data_m[i + 1]));
        data_m[i + 1].~T();
    }

    --size_m;

    return iterator(data_m + index);
}

template<typename T>
typename my_vector<T>::iterator my_vector<T>::erase(const_iterator first, const_iterator last) {
    if (first == last) return iterator(first);

    size_t start = first - const_iterator(data_m);
    size_t end = last - const_iterator(data_m);

    for (size_t i = start; i < end; ++i) {
        data_m[i].~T();
    }

    for (size_t i = end; i < size_m; ++i) {
        new(&data_m[start + i - end]) T(std::move(data_m[i]));
        data_m[i].~T();
    }

    size_m -= (end - start);
    return iterator(data_m + start);
}

template<typename T>
void my_vector<T>::pop_back() {
    size_m--;
}

template<typename T>
void my_vector<T>::push_back(const T &value) {
    if (size_m >= capacity_m) {
        reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
    }

    data_m[size_m++] = value;
}

template<typename T>
void my_vector<T>::push_back(T &&value) {
    if (size_m >= capacity_m) {
        reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
    }

    data_m[size_m++] = std::forward<T>(value);
}

template<typename T>
template<class... Args>
typename my_vector<T>::reference my_vector<T>::emplace_back(Args &&... args) {
    if (size_m >= capacity_m) {
        reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
    }

    new(&data_m[size_m++]) T(std::forward<Args>(args)...);

    return data_m[size_m - 1];
}

// template<typename T>
// template<class ... Args>
// typename my_vector<T>::iterator my_vector<T>::emplace( const_iterator pos, Args&&... args )
// {
//     size_t index = pos - data_m;  // Convert const_iterator to index
//
//     if (size_m >= capacity_m) {
//         reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
//     }
//
//     // Move elements to the right to make space
//     for (size_t i = size_m; i > index; --i) {
//         new (&data_m[i]) T(std::move(data_m[i - 1]));
//         data_m[i - 1].~T();
//     }
//
//     // Construct the new element in-place using perfect forwarding
//     new (&data_m[index]) T(std::forward<Args>(args)...);
//
//     ++size_m;
//     return data_m + index;
// }

template<typename T>
my_vector<T> &my_vector<T>::operator=(const my_vector &other) {
    reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
    size_m = other.size_m;
    for (size_t i = 0; i < size_m; i++) {
        data_m[i] = other.data_m[i];
    }

    return *this;
}

template<typename T>
my_vector<T> &my_vector<T>::operator=(std::initializer_list<T> ilist) {
    assign(ilist);
    return *this;
}

template<typename T>
my_vector<T> &my_vector<T>::operator=(my_vector &&other) noexcept {
    if (this == &other) return *this;

    clear();

    data_m = other.data_m;
    size_m = other.size_m;
    capacity_m = other.capacity_m;

    other.clear();

    return *this;
}

template<typename T>
typename my_vector<T>::reference my_vector<T>::front() {
    return data_m[0];
}

template<typename T>
typename my_vector<T>::const_reference my_vector<T>::front() const {
    return data_m[0];
}

template<typename T>
typename my_vector<T>::reference my_vector<T>::back() {
    return data_m[size_m - 1];
}

template<typename T>
typename my_vector<T>::const_reference my_vector<T>::back() const {
    return data_m[size_m - 1];
}

template<typename T>
T &my_vector<T>::operator[](size_t index) {
    return data_m[index];
}

template<typename T>
const T &my_vector<T>::at(size_t index) const {
    if (index >= size_m) {
        throw std::out_of_range("index out of range");
    }

    return data_m[index];
}

template<typename T>
T &my_vector<T>::operator[](size_t index) const {
    if (index >= size_m) {
        throw std::out_of_range("index out of range");
    }

    return data_m[index];
}

template<typename T>
void my_vector<T>::swap(my_vector &other) noexcept {
    std::swap(size_m, other.size_m);
    std::swap(capacity_m, other.capacity_m);
    std::swap(data_m, other.data_m);
}

template<typename T>
void my_vector<T>::clear() {
    for (size_t i = 0; i < size_m; i++) {
        std::destroy_at(&data_m[i]);
    }

    data_m = nullptr;
    size_m = 0;
    capacity_m = 0;
}

template<typename T>
void my_vector<T>::resize(size_t new_size) {
    if (size_m > new_size) {
        size_m = new_size;
    } else {
        size_m = new_size;
        reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
    }
}

template<typename T>
void my_vector<T>::reserve(size_t new_capacity) {
    if (capacity_m > new_capacity) {
        return;
    }

    capacity_m = new_capacity;
    T * new_data_m = static_cast<T *>(::operator new(capacity_m * sizeof(T)));

    for (size_t i = 0; i < size_m; ++i) {
        // new_data_m[i] = data_m[i];
        new(&new_data_m[i]) T(data_m[i]);
        std::destroy_at(&data_m[i]);
    }

    ::operator delete(data_m);
    data_m = new_data_m;
}

template<typename T>
size_t my_vector<T>::capacity() const {
    return capacity_m;
}

template<typename T>
size_t my_vector<T>::size() const {
    return size_m;
}

template<typename T>
void my_vector<T>::shrink_to_fit() {
    reserve(SIZE_MULT * size_m);
}

template<typename T>
void my_vector<T>::resize(size_t new_size, const T &new_element) {
    if (size_m > new_size) {
        size_m = new_size;
    } else {
        size_t begin = size_m;
        size_m = new_size;
        reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
        for (size_t i = begin; i < size_m; i++) {
            data_m[i] = new_element;
        }
    }
}

template<typename T>
template<class InputIt>
typename my_vector<T>::iterator my_vector<T>::insert(const_iterator pos, InputIt first, InputIt last) {
    size_t index = pos - const_iterator(data_m);
    size_t count = std::distance(first, last);

    if (count == 0) {
        return iterator(data_m + index);
    }

    if (size_m + count >= capacity_m) {
        reserve(std::max(capacity_m * SIZE_MULT, size_m + count));
    }

    for (size_t i = size_m; i > index; --i) {
        new(&data_m[i + count - 1]) T(std::move(data_m[i - 1]));
        data_m[i - 1].~T();
    }

    size_t insert_i = index;
    for (; first != last; ++first, ++insert_i) {
        new(&data_m[insert_i]) T(*first);
    }

    size_m += count;
    return iterator(data_m + index);
}

template<typename T>
typename my_vector<T>::iterator my_vector<T>::insert(const_iterator pos, const T &value) {
    size_t index = pos - const_iterator(data_m);

    if (size_m >= capacity_m) {
        reserve(SIZE_MULT * std::max(MIN_VECTOR_LEN, size_m));
    }

    for (size_t i = size_m; i > index; --i) {
        new(&data_m[i]) T(std::move(data_m[i - 1]));
        data_m[i - 1].~T();
    }

    new(&data_m[index]) T(value);
    ++size_m;

    return iterator(data_m + index);
}

template<class T>
bool operator==(const my_vector<T> &lhs, const my_vector<T> &rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template<class T>
bool operator!=(const my_vector<T> &lhs, const my_vector<T> &rhs) {
    return !(lhs == rhs);
}

template<class T>
bool operator<(const my_vector<T> &lhs, const my_vector<T> &rhs) {
    size_t min_size = std::min(lhs.size(), rhs.size());

    for (size_t i = 0; i < min_size; ++i) {
        if (lhs[i] < rhs[i]) return true;
        if (rhs[i] < lhs[i]) return false;
    }

    return lhs.size() < rhs.size();
}

template<class T>
bool operator<=(const my_vector<T> &lhs, const my_vector<T> &rhs) {
    if (lhs < rhs) return true;

    return lhs == rhs;
}

template<class T>
bool operator>(const my_vector<T> &lhs, const my_vector<T> &rhs) {
    if (lhs < rhs) return false;
    if (lhs == rhs) return false;

    return true;
}

template<class T>
bool operator>=(const my_vector<T> &lhs, const my_vector<T> &rhs) {
    if (lhs < rhs) return false;
    if (lhs == rhs) return true;

    return true;
}

#endif //MY_VECTOR_H

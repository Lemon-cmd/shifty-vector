#include <assert.h>
#include <cstring>
#include <utility>

template <typename T>
struct svector {
	/* Self-implemented vector structure for C++ */
	protected:
		size_t _size = 0;											//num. of items
		size_t _bsize = 20;											//initial buffer size
		size_t _growth = 15;										//initial limit
		T* buffer = new T[_bsize];									//buffer
	
	public:
		svector() = default;										//default constructor
		
		svector(const size_t &&len, const T num) {					//optional constructor
			for (int j = 0; j < len; j ++)							//does not work well with std::string when len > 100
				push_back(num);
		}	

		~svector() {												//destructors
			delete [] buffer;
		}
		svector (const svector&) = delete;
		svector& operator=(const svector&) = delete;
		
		T& operator[](const unsigned int && n) {					//indexing operator return ref
			assert(_size > 0);
			return buffer[n];
		}
		
		void push_back(const T& item)								//push_back &ref method;
		{		
			buffer[_size] = item;									//add item
			_size ++;												//increment size
			if (_size == _growth) {
				_bsize += _bsize / 2;								//new size
				T* new_buffer = new T[_bsize];						//new buffer
				memcpy(new_buffer, buffer, _size * sizeof(T));		//cpy memory of old buffer
				_growth = _bsize * 0.75;							//new limit
				delete [] buffer; buffer = new_buffer;				//delete and set new
			}
		}
		
		void push_back(const T&& item)								//push_back temp/L value method;
		{
			buffer[_size] = std::move(item);
			_size ++;
			if (_size == _growth) {
				_bsize += _bsize / 2;
				T* new_buffer = new T[_bsize];
				memcpy(new_buffer, buffer, _size * sizeof(T));
				_growth = _bsize * 0.75;
				delete [] buffer; buffer = new_buffer;
			}
		}

		constexpr size_t size() {									//return size;
			return _size;
		}
};

#include <iostream>
int main() {
	svector<int> V (1000000, 15);
	std::cout << V.size() << "\n";
	for (int j = 0; j < V.size(); j++){
		std::cout << V[j] << " ";
	}
}

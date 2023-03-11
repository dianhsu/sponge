#include "byte_stream.hh"
#include <deque>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : _capacity(capacity), _read_count(0), _write_count(0), _input_end(false), _mem() { }

size_t ByteStream::write(const string &data) {
    size_t _copy = min(data.length(), _capacity - _mem.size());
    for(size_t i = 0; i < _copy; ++i){
      _mem.push_back(data[i]);
    }
    _write_count += _copy;
    return _copy;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t _copy = min(len, _mem.size());
    string _peek;
    for(size_t i = 0; i < _copy; ++i){
      _peek += _mem[i];
    }
    return _peek;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t _copy = min(len, _mem.size());
    for(size_t i = 0; i < _copy; ++i){
      _mem.pop_front();
    }
    _read_count += _copy;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    size_t _copy = min(len, _mem.size());
    string _read;
    for(size_t i = 0; i < _copy; ++i){
      _read += _mem[i];
    }
    for(size_t i = 0; i < _copy; ++i){
      _mem.pop_front();
    }
    return _read;
}

void ByteStream::end_input() {
  _input_end = true;
}

bool ByteStream::input_ended() const { return _input_end; }

size_t ByteStream::buffer_size() const { return _mem.size(); }

bool ByteStream::buffer_empty() const { return _mem.empty(); }

bool ByteStream::eof() const { return _mem.empty() and _input_end; }

size_t ByteStream::bytes_written() const { return _write_count; }

size_t ByteStream::bytes_read() const { return _read_count; }

size_t ByteStream::remaining_capacity() const { return _capacity - _mem.size(); }

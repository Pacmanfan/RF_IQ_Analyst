#ifndef CIRCBUFF_H
#define CIRCBUFF_H

#include <algorithm> // for std::min
#include <mutex>
#include <condition_variable>
#include "string.h"

#define CBLOCKING 1

template<typename T>
class CircBuff
{
public:
#if(CBLOCKING == 1)
    typedef std::lock_guard<std::mutex> lock;
#endif

    CircBuff(size_t capacity)
    {
        beg_index_ = 0;
        end_index_ = 0;
        size_ = 0;
        capacity_ = capacity;
        data_ = new T[capacity];
    }

    ~CircBuff()
    {
        delete [] data_;
    }

    /*
        returns numer of free positions
    */
    size_t remaining_free()
    {
    #if(CBLOCKING == 1)
        lock lk(monitor);
    #endif
        return capacity_ - size_;
    }

    size_t size() // returns the number of items in storage
    {
    #if(CBLOCKING == 1)
        lock lk(monitor);
    #endif
        return size_;
    }

    size_t capacity() const { return capacity_; }
  // Return number of bytes written.

    size_t write(const T *data, size_t numitems)
    {
        #if(CBLOCKING == 1)
        lock lk(monitor);
        #endif
        if (numitems == 0) return 0;

        size_t capacity = capacity_;
        //size_t items_to_write = std::min(numitems, capacity - size_);
        size_t items_to_write = numitems;// always write, even if it overwrites.... std::min(numitems, capacity - size_);

        // Write in a single step
        if (items_to_write <= capacity - end_index_)
        {
            memcpy(data_ + end_index_, data, items_to_write * sizeof(T));
            end_index_ += items_to_write;
            if (end_index_ == capacity)
                end_index_ = 0;
        }
        // Write in two steps
        else
        {
            size_t size_1 = capacity - end_index_;
            memcpy(data_ + end_index_, data, size_1 * sizeof(T));
            size_t size_2 = items_to_write - size_1;
            memcpy(data_, data + size_1, size_2 * sizeof(T));
            end_index_ = size_2;
        }

        size_ += items_to_write;
        if(size_ > capacity_)  size_ = capacity_; // full up
        return items_to_write;
    }
  // Return number of bytes read.
    size_t read(T *data, size_t numitems)
    {
        #if(CBLOCKING == 1)
        lock lk(monitor);
        #endif
        if (numitems == 0)
            return 0;

        size_t capacity = capacity_;
        size_t items_to_read = std::min(numitems, size_);

        // Read in a single step
        if (items_to_read <= capacity - beg_index_)
        {
            memcpy(data, data_ + beg_index_, items_to_read * sizeof(T));
            beg_index_ += items_to_read;
            if (beg_index_ == capacity)
                beg_index_ = 0;
        }
        // Read in two steps
        else
        {
            size_t size_1 = capacity - beg_index_;
            memcpy(data, data_ + beg_index_, size_1 * sizeof(T));
            size_t size_2 = items_to_read - size_1;
            memcpy(data + size_1, data_, size_2 * sizeof(T));
            beg_index_ = size_2;
        }

        size_ -= items_to_read;
        return items_to_read;
    }
        //skip the specified number of items in the circular buffer
        //essentially dropping them on the floor
        // Return number of items skipped.
      size_t skip(size_t numitems)
      {
          #if(CBLOCKING == 1)
          lock lk(monitor);
          #endif
          if (numitems == 0)
              return 0;

          size_t capacity = capacity_;
          size_t items_to_read = std::min(numitems, size_);

          // Read in a single step
          if (items_to_read <= capacity - beg_index_)
          {
              beg_index_ += items_to_read;
              if (beg_index_ == capacity)
                  beg_index_ = 0;
          }
          // Read in two steps
          else
          {
              size_t size_1 = capacity - beg_index_;
              size_t size_2 = items_to_read - size_1;
              beg_index_ = size_2;
          }

          size_ -= items_to_read;
          return items_to_read;
      }
    //Read, but don't advance the read index to consume
      size_t peek(T *data, size_t numitems)
      {
          #if(CBLOCKING == 1)
          lock lk(monitor);
          #endif
          if (numitems == 0)
              return 0;

          size_t capacity = capacity_;
          size_t items_to_read = std::min(numitems, size_);

          // Read in a single step
          if (items_to_read <= capacity - beg_index_)
          {
              memcpy(data, data_ + beg_index_, items_to_read * sizeof(T));
              beg_index_ += items_to_read;
              if (beg_index_ == capacity)
                  beg_index_ = 0;
          }
          // Read in two steps
          else
          {
              size_t size_1 = capacity - beg_index_;
              memcpy(data, data_ + beg_index_, size_1 * sizeof(T));
              size_t size_2 = items_to_read - size_1;
              memcpy(data + size_1, data_, size_2 * sizeof(T));
              beg_index_ = size_2;
          }

          //size_ -= items_to_read;
          return items_to_read;
      }

    void clear()
    {
    #if(CBLOCKING == 1)
        lock lk(monitor);
    #endif
        size_ = 0; // move to beginning position
        beg_index_ = 0;
        end_index_ = 0;
    }

private:
  size_t beg_index_, end_index_, size_, capacity_;
  T *data_;
#if(CBLOCKING == 1)
    std::condition_variable buffer_not_empty;
    std::mutex monitor;
#endif
};

//Same as above, but no locking, so it's not thread safe...

template<typename T>
class CircBuff_No_lock
{
public:

    CircBuff_No_lock(size_t capacity)
    {
        beg_index_ = 0;
        end_index_ = 0;
        size_ = 0;
        capacity_ = capacity;
        data_ = new T[capacity];
    }

    ~CircBuff_No_lock()
    {
        delete [] data_;
    }

    /*
        returns numer of free positions
    */
    size_t remaining_free()
    {
        return capacity_ - size_;
    }

    size_t size() // returns the number of items in storage
    {
        return size_;
    }

    size_t capacity() const { return capacity_; }
  // Return number of bytes written.

    size_t write(const T *data, size_t numitems)
    {
        if (numitems == 0) return 0;

        size_t capacity = capacity_;
        size_t items_to_write = std::min(numitems, capacity - size_);

        // Write in a single step
        if (items_to_write <= capacity - end_index_)
        {
            memcpy(data_ + end_index_, data, items_to_write * sizeof(T));
            end_index_ += items_to_write;
            if (end_index_ == capacity)
                end_index_ = 0;
        }
        // Write in two steps
        else
        {
            size_t size_1 = capacity - end_index_;
            memcpy(data_ + end_index_, data, size_1 * sizeof(T));
            size_t size_2 = items_to_write - size_1;
            memcpy(data_, data + size_1, size_2 * sizeof(T));
            end_index_ = size_2;
        }

        size_ += items_to_write;
        return items_to_write;
    }
  // Return number of bytes read.
    size_t read(T *data, size_t numitems)
    {
        if (numitems == 0)
            return 0;

        size_t capacity = capacity_;
        size_t items_to_read = std::min(numitems, size_);

        // Read in a single step
        if (items_to_read <= capacity - beg_index_)
        {
            memcpy(data, data_ + beg_index_, items_to_read * sizeof(T));
            beg_index_ += items_to_read;
            if (beg_index_ == capacity)
                beg_index_ = 0;
        }
        // Read in two steps
        else
        {
            size_t size_1 = capacity - beg_index_;
            memcpy(data, data_ + beg_index_, size_1 * sizeof(T));
            size_t size_2 = items_to_read - size_1;
            memcpy(data + size_1, data_, size_2 * sizeof(T));
            beg_index_ = size_2;
        }

        size_ -= items_to_read;
        return items_to_read;
    }
    //skip the specified number of items in the circular buffer
    //essentially dropping them on the floor
    // Return number of items skipped.
    size_t skip(size_t numitems)
    {
      if (numitems == 0)
          return 0;

      size_t capacity = capacity_;
      size_t items_to_read = std::min(numitems, size_);

      // Read in a single step
      if (items_to_read <= capacity - beg_index_)
      {
          beg_index_ += items_to_read;
          if (beg_index_ == capacity)
              beg_index_ = 0;
      }
      // Read in two steps
      else
      {
          size_t size_1 = capacity - beg_index_;
          size_t size_2 = items_to_read - size_1;
          beg_index_ = size_2;
      }

      size_ -= items_to_read;
      return items_to_read;
    }

    //Read, but don't advance the read index to consume
    size_t peek(T *data, size_t numitems)
    {
        if (numitems == 0)
            return 0;

        size_t capacity = capacity_;
        size_t items_to_read = std::min(numitems, size_);

        // Read in a single step
        if (items_to_read <= capacity - beg_index_)
        {
            memcpy(data, data_ + beg_index_, items_to_read * sizeof(T));
            beg_index_ += items_to_read;
            if (beg_index_ == capacity)
              beg_index_ = 0;
        }
        // Read in two steps
        else
        {
            size_t size_1 = capacity - beg_index_;
            memcpy(data, data_ + beg_index_, size_1 * sizeof(T));
            size_t size_2 = items_to_read - size_1;
            memcpy(data + size_1, data_, size_2 * sizeof(T));
            beg_index_ = size_2;
        }

        //size_ -= items_to_read;
        return items_to_read;
    }
    void clear()
    {
        size_ = 0; // move to beginning position
        beg_index_ = 0;
        end_index_ = 0;
    }

private:
  size_t beg_index_, end_index_, size_, capacity_;
  T *data_;
};


#endif // CIRCULARBUFFER_H

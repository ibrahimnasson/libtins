/*
 * Copyright (c) 2012, Nasel
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef TINS_IPV6_ADDRESS
#define TINS_IPV6_ADDRESS

#include <string>
#include <stdexcept>
#include <stdint.h>

namespace Tins {
class IPv6Address {
public:
    /**
     * The exception thrown when a malformed address is parsed.
     */
    class malformed_address : public std::exception {
    public:
        const char *what() const throw() {
            return "Malformed address";
        }
    };
    
    static const size_t address_size = 16;
    
    /**
     * The iterator type.
     */
    typedef uint8_t* iterator;
    
    /**
     * The const iterator type.
     */
    typedef const uint8_t* const_iterator;

    /**
     * \brief Default constructor.
     * Initializes this IPv6 address to "::"
     */
    IPv6Address();
    
    /**
     * \brief Constructor from a text representation.
     * \param addr The text representation from which to construct this
     * object.
     */
    IPv6Address(const std::string &addr);
    
    /**
     * \brief Retrieve the string representation of this address.
     * 
     * \return std::string containing the representation of this address.
     */
    std::string to_string() const;
    
    /**
     * Returns an iterator to the beginning of this address.
     */
    iterator begin() {
        return address;
    }
    
    /**
     * Returns a const iterator to the beginning of this address.
     */
    const_iterator begin() const {
        return address;
    }
    
    /**
     * Returns an iterator to the one-past-the-end element of this address.
     */
    iterator end() {
        return address + address_size;
    }
    
    /**
     * Returns a const iterator to the one-past-the-end element of this 
     * address.
     */
    const_iterator end() const {
        return address + address_size;
    }
    
    /**
     * \brief Compares this address for equality.
     * 
     * \param rhs The address to be compared to.
     * 
     * \return bool indicating whether addresses are equal.
     */
    bool operator==(const IPv6Address &rhs) const {
        return std::equal(begin(), end(), rhs.begin());
    }
    
    /**
     * \brief Compares this address for inequality.
     * 
     * \param rhs The address to be compared to.
     * 
     * \return bool indicating whether addresses are distinct.
     */
    bool operator!=(const IPv6Address &rhs) const {
        return !(*this == rhs);
    }
    
    /**
     * \brief Compares this address for less-than inequality.
     * 
     * \param rhs The address to be compared to.
     * 
     * \return bool indicating whether this address is less-than rhs.
     */
    bool operator<(const IPv6Address &rhs) const {
        return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
    }
    
    /**
     * \brief Helper function which copies the address into an output
     * iterator.
     * 
     * This is the same as:
     * 
     * std::copy(begin(), end(), iter);
     * 
     * But since some PDUs return a IPv6Address by value, this function
     * can be used to avoid temporaries. 
     * 
     * \param iter The output iterator in which to store this address.
     * \return OutputIterator pointing to one-past the last position
     * written.
     */
    template<typename OutputIterator>
    OutputIterator copy(OutputIterator iter) const {
        return std::copy(begin(), end(), iter);
    }
    
    /**
     * \brief Writes this address in hex-notation to a std::ostream.
     * 
     * \param os The stream in which to write the address.
     * \param addr The parameter to be written.
     * \return std::ostream& pointing to the os parameter.
     */
    friend std::ostream &operator<<(std::ostream &os, const IPv6Address &addr) {
        return os << addr.to_string();
    }
private:
    uint8_t address[address_size];
};
}

#endif // TINS_IPV6_ADDRESS
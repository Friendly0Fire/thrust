/*
 *  Copyright 2008-2013 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file thrust/system/omp/vector.h
 *  \brief A dynamically-sizable array of elements which reside in memory available to
 *         Thrust's OpenMP system.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/system/omp/memory.h>
#include <thrust/detail/vector_base.h>
#include <vector>

namespace thrust
{

// forward declaration of host_vector
// XXX why is this here? it doesn't seem necessary for anything below
template<typename T, typename Allocator> class host_vector;

namespace system
{
namespace omp
{

// XXX upon c++11
// template<typename T, typename Allocator = allocator<T> > using vector = thrust::detail::vector_base<T,Allocator>;

/*! \p omp::vector is a container that supports random access to elements,
 *  constant time removal of elements at the end, and linear time insertion
 *  and removal of elements at the beginning or in the middle. The number of
 *  elements in a \p omp::vector may vary dynamically; memory management is
 *  automatic. The elements contained in an \p omp::vector reside in memory
 *  available to the \p omp system.
 *
 *  \tparam T The element type of the \p omp::vector.
 *  \tparam Allocator The allocator type of the \p omp::vector. Defaults to \p omp::allocator.
 *
 *  \see http://www.sgi.com/tech/stl/Vector.html
 *  \see host_vector For the documentation of the complete interface which is
 *                   shared by \p omp::vector
 *  \see device_vector
 */
template<typename T, typename Allocator = allocator<T> >
  class vector
    : public thrust::detail::vector_base<T,Allocator>
{
  /*! \cond
   */
  private:
    typedef thrust::detail::vector_base<T,Allocator> super_t;
  /*! \endcond
   */

  public:

  /*! \cond
   */
    typedef typename super_t::size_type  size_type;
    typedef typename super_t::value_type value_type;
  /*! \endcond
   */

    /*! This constructor creates an empty \p omp::vector.
     */
    vector();

    /*! This constructor creates a \p omp::vector with \p n default-constructed elements.
     *  \param n The size of the \p omp::vector to create.
     */
    explicit vector(size_type n);

    /*! This constructor creates a \p omp::vector with \p n copies of \p value.
     *  \param n The size of the \p omp::vector to create.
     *  \param value An element to copy.
     */
    explicit vector(size_type n, const value_type &value);

    /*! Copy constructor copies from another \p omp::vector.
     *  \param x The other \p omp::vector to copy.
     */
    vector(const vector &x);

  #if __cplusplus >= 201103L
    /*! Move constructor moves another \p omp::vector.
     *  \param x The other \p omp::vector to move from.
     */
    vector(vector &&x);
  #endif

    /*! This constructor copies from another Thrust vector-like object.
     *  \param x The other object to copy from.
     */
    template<typename OtherT, typename OtherAllocator>
    vector(const thrust::detail::vector_base<OtherT,OtherAllocator> &x);

    /*! This constructor copies from a \c std::vector.
     *  \param x The \c std::vector to copy from.
     */
    template<typename OtherT, typename OtherAllocator>
    vector(const std::vector<OtherT,OtherAllocator> &x);

    /*! This constructor creates an \p omp::vector by copying from a range.
     *  \param first The beginning of the range.
     *  \param last The end of the range.
     */
    template<typename InputIterator>
    vector(InputIterator first, InputIterator last);

    // XXX vector_base should take a Derived type so we don't have to define these superfluous assigns

    /*! Copy assignment operator assigns from another \p omp::vector.
    *  \param x The other object to assign from.
    *  \return <tt>*this</tt>
    */
   vector &operator=(const vector &x);

  #if __cplusplus >= 201103L
    /*! Move assignment operator moves another \p omp::vector.
     *  \param x The other \p omp::vector to move.
     *  \return <tt>*this</tt>
     */
     vector &operator=(vector &&x);
  #endif

    /*! Assignment operator assigns from a \c std::vector.
     *  \param x The \c std::vector to assign from.
     *  \return <tt>*this</tt>
     */
    template<typename OtherT, typename OtherAllocator>
    vector &operator=(const std::vector<OtherT,OtherAllocator> &x);

    /*! Assignment operator assigns from another Thrust vector-like object.
     *  \param x The other object to assign from.
     *  \return <tt>*this</tt>
     */
    template<typename OtherT, typename OtherAllocator>
    vector &operator=(const thrust::detail::vector_base<OtherT,OtherAllocator> &x);
}; // end vector

} // end omp
} // end system

// alias system::omp names at top-level
namespace omp
{

using thrust::system::omp::vector;

} // end omp

} // end thrust

#include <thrust/system/omp/detail/vector.inl>


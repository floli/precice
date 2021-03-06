#pragma once

#include <vector>
#include <cstddef>
#include <iterator>
#include <memory>

namespace precice {
  namespace mesh {
    class Mesh;
    class Group;
  }
  namespace impl {
    struct VertexIteratorImplementation;
    struct EdgeIteratorImplementation;
    struct TriangleIteratorImplementation;
    // no quad iterator yet
  }
}


// ----------------------------------------------------------- CLASS DEFINITION

namespace precice {

/// Iterator over vertex coordinates and IDs.
class VertexIterator
{
public:
  using value_type        = VertexIterator;
  using reference         = VertexIterator &;
  using pointer           = VertexIterator *;
  using difference_type   = std::size_t;
  using iterator_category = std::forward_iterator_tag;

  VertexIterator();

  ~VertexIterator();

  VertexIterator (
    const mesh::Group& content,
    bool               begin );

  VertexIterator ( const VertexIterator& other );

  VertexIterator& operator= ( const VertexIterator& other );

  /// Postfix operator
  VertexIterator operator++(int unused);

  /// Prefix operator
  VertexIterator& operator++();

  const VertexIterator operator*() const;

  int vertexID() const;

  const double* vertexCoords() const;

  bool operator== ( const VertexIterator& other ) const;

  bool operator!= ( const VertexIterator& other ) const;

  void swap(VertexIterator& other) noexcept;

private:
  using Impl = impl::VertexIteratorImplementation;
  std::unique_ptr<Impl> _impl;
};

void swap(VertexIterator& lhs, VertexIterator& rhs) noexcept;

/// Offers methods begin() and end() to iterate over all vertices.
class VertexHandle
{
public:

  using const_iterator = VertexIterator;

  /// Constructor, reference to mesh object holding vertices required.
  VertexHandle ( const mesh::Group& content );

  /// Returns iterator to begin of the geometry's vertices.
  VertexIterator begin() const;

  /// Returns iterator to end of the geometry's vertices.
  VertexIterator end() const;

  std::size_t size() const;

private:

  /// Group instance holding vertices.
  const mesh::Group& _content;
};

class EdgeIterator
{
public:
  using value_type        = EdgeIterator;
  using reference         = EdgeIterator &;
  using pointer           = EdgeIterator *;
  using difference_type   = std::size_t;
  using iterator_category = std::forward_iterator_tag;

  EdgeIterator ();

  ~EdgeIterator ();

  EdgeIterator (
    const mesh::Group& mesh,
    bool              begin );


  EdgeIterator (const EdgeIterator& other);

  EdgeIterator& operator=(const EdgeIterator& other);

  EdgeIterator operator++(int);

  EdgeIterator& operator++();

  const EdgeIterator operator*() const;

  const double* vertexCoords ( int vertexIndex ) const;

  int vertexID ( int vertexIndex ) const;

  bool operator== ( const EdgeIterator& other ) const;

  bool operator!= ( const EdgeIterator& other ) const;

  void swap(EdgeIterator& other) noexcept;

private:
  using Impl = impl::EdgeIteratorImplementation;
  std::unique_ptr<Impl> _impl;
};

void swap(EdgeIterator& lhs, EdgeIterator& rhs) noexcept;

/**
 * @brief Offers methods begin() and end() to iterate over all edges.
 */
class EdgeHandle
{
public:

  using const_iterator = EdgeIterator;

   /**
    * @brief Constructor, reference to mesh object holding edges required.
    */
   EdgeHandle ( const mesh::Group& mesh );

   /**
    * @brief Returns iterator to begin of the geometry's edges.
    */
   EdgeIterator begin() const;

   /**
    * @brief Returns iterator to end of the geometry's edges.
    */
   EdgeIterator end() const;

  std::size_t size() const;

private:

   // @brief Mesh instance holding edges.
   const mesh::Group& _content;
};

class TriangleIterator
{
public:
  using value_type        = TriangleIterator;
  using reference         = TriangleIterator &;
  using pointer           = TriangleIterator *;
  using difference_type   = std::size_t;
  using iterator_category = std::forward_iterator_tag;

  TriangleIterator();

  ~TriangleIterator();

  TriangleIterator (
    const mesh::Group& content,
    bool               begin );

  TriangleIterator (const TriangleIterator& other);

  TriangleIterator& operator=(const TriangleIterator& other);

  TriangleIterator operator++(int);

  TriangleIterator& operator++();

  const TriangleIterator operator*() const;

  const double* vertexCoords ( int vertexIndex ) const;

  int vertexID ( int vertexIndex ) const;

  bool operator== ( const TriangleIterator& other ) const;

  bool operator!= ( const TriangleIterator& other ) const;

  void swap(TriangleIterator& other) noexcept;

private:
  using Impl = impl::TriangleIteratorImplementation;
  std::unique_ptr<Impl> _impl;
};

void swap(TriangleIterator& lhs, TriangleIterator& rhs) noexcept;

/**
 * @brief Offers methods begin() and end() to iterate over all triangles.
 */
class TriangleHandle
{
public:

  using const_iterator = TriangleIterator;

   /**
    * @brief Constructor, reference to mesh object holding triangles required.
    */
   TriangleHandle ( const mesh::Group& content );

   /**
    * @brief Returns iterator to begin of the geometry's triangles.
    */
   TriangleIterator begin() const;

   /**
    * @brief Returns iterator to end of the geometry's triangles.
    */
   TriangleIterator end() const;

  std::size_t size() const;

private:

   /// Mesh instance holding triangles.
   const mesh::Group& _content;
};

/**
 * @brief Allows to query vertices, edges, and triangles of a geometry.
 *
 * A geometry handle can be retrieved from the coupling interface by the method
 * precice::SolverInterfaceImpl::getMeshHandle().
 *
 * Access to vertices is done via the method precice::MeshHandle::vertices(),
 * which returns a MeshHandle::VertexHandle object, which offers the
 * methods begin() and end() to iterate over all vertices. Access to edges and
 * triangles is analogous.
 *
 * The iterators return const references to the respective objects on dereferenciation
 * by using operator*(). The operator -> is not supported, and does only return
 * pointers to the objects.
 */
class MeshHandle
{
public:

   /**
    * @brief Standard constructor, not meant to be used by a solver.
    *
    * @param[in] mesh The mesh representing the geometry.
    */
   MeshHandle ( const mesh::Group& content );

   /**
    * @brief Returns handle for Vertex objects.
    */
   const VertexHandle& vertices () const;

   /**
    * @brief Returns handle for Edge objects.
    */
   const EdgeHandle& edges () const;

   /**
    * @brief Returns handle for Triangle objects.
    */
   const TriangleHandle& triangles () const;

private:

   /// Handle for vertices.
   VertexHandle _vertexHandle;

   /// Handle for edges.
   EdgeHandle _edgeHandle;

   /// Handle for triangles.
   TriangleHandle _triangleHandle;
};

} // namespace precice

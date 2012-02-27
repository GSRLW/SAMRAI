/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Iterator over real Boxes in a BoxContainer.
 *
 ************************************************************************/
#ifndef included_hier_RealBoxConstIterator
#define included_hier_RealBoxConstIterator

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/hier/BoxContainer.h"

namespace SAMRAI {
namespace hier {


/*
 * TODO: Do we really need a separate class for this?  Couldn't we just
 *       add an argument to the BoxContainer iterator construction that
 *       (e.g., an enum with values: All (default value), RealOnly,
 *       PeriodicImagesOnly, etc.  and extend for Multiblock stuff)?
 *       Then, which boxes in the set are selected for iteration would be
 *       controlled internally.
 */
/*!
 * @brief Iterator through real Boxes (not periodic images) in a
 * const BoxContainer.
 *
 * RealBoxConstIterator is an iterator that provides methods for
 * stepping through a BoxContainer, skipping periodic images.
 *
 * Example usage:
 * @verbatim
 *  BoxContainer mapped_boxes;
 *  // fill in mapped_boxes
 *  for ( RealBoxConstIterator ni(mapped_boxes); ni.isValid(); ++ni ) {
 *    TBOX_ASSERT( ! ni->isPeriodicImage() );
 *  }
 * @endverbatim
 */
class RealBoxConstIterator
{

public:
   /*!
    * @brief Construct the iterator for the given BoxContainer.
    *
    * The iterator will iterate through the items in mapped_boxes.
    *
    * @param[in] mapped_boxes
    */
   explicit RealBoxConstIterator(
      const BoxContainer& mapped_boxes);

   /*!
    * @brief Destructor.
    */
   ~RealBoxConstIterator();

   /*!
    * @brief Assignment operator.
    */
   RealBoxConstIterator&
   operator = (
      const RealBoxConstIterator& r);

   /*!
    * @brief Dereference operator mimicking a pointer dereference.
    */
   const Box&
   operator * () const;

   /*!
    * @brief Dereference operator mimicking a pointer dereference.
    */
   const Box *
   operator -> () const;

   /*!
    * @brief Equality comparison.
    */
   bool
   operator == (
      const RealBoxConstIterator& r) const;

   /*!
    * @brief Inequality comparison.
    */
   bool
   operator != (
      const RealBoxConstIterator& r) const;

   /*!
    * @brief Pre-increment iterator.
    *
    * Pre-increment increment the iterator and returns the incremented
    * state.
    */
   RealBoxConstIterator&
   operator ++ ();

   /*!
    * @brief Post-increment iterator.
    *
    * Post-increment saves the iterator, increment it and returns the
    * saved iterator.
    */
   RealBoxConstIterator
   operator ++ (
      int);

   /*!
    * @brief Whether the iterator can be dereferenced.  When the
    * iterator reaches its end, this returns false.
    */
   bool
   isValid() const;

private:
   /*!
    * @brief BoxContainer being iterated through.
    */
   const BoxContainer* d_mapped_boxes;

   /*!
    * @brief The iterator.
    */
   BoxContainer::ConstIterator d_ni;

};

}
}

#ifdef SAMRAI_INLINE
#include "SAMRAI/hier/RealBoxConstIterator.I"
#endif
#endif  // included_hier_RealBoxConstIterator

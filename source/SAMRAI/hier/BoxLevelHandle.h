/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Auto-release handle to prevent using invalid Connector data.
 *
 ************************************************************************/
#ifndef included_hier_BoxLevelHandle
#define included_hier_BoxLevelHandle

#include "SAMRAI/SAMRAI_config.h"

#include <boost/make_shared.hpp>

namespace SAMRAI {
namespace hier {

class BoxLevel;

/*!
 * @brief A handle for Connectors to access their head and base
 * BoxLevels.  A BoxLevel automatically releases its
 * handle when it changes in a way that can invalidate Connector data,
 * preventing the use of inconsistent data and deallocated objects.
 *
 * Connector data can become invalid if the base or head
 * BoxLevel changes in certain ways, such as being
 * re-initialized or going out of scope.  This class is a mechanism to
 * prevent inappropriately using Connectors with invalid data.
 *
 * A BoxLevelHandle is generated by a BoxLevel and sits
 * between the BoxLevel and all Connectors referencing the
 * BoxLevel.  Connectors sensing that the BoxLevel has
 * been disconnected has a chance to reset themselves to avoid using
 * invalid data.
 *
 * @see BoxLevel::getBoxLevelHandle()
 */

class BoxLevelHandle
{

public:
   /*!
    * @brief Destructor detaches the handle from its BoxLevel,
    * if it is still attached.
    */
   ~BoxLevelHandle();

   /*!
    * @brief Return the BoxLevel attached to this handle.
    *
    * If there is no attached BoxLevel (isAttached() returns
    * false), an assertion is thrown.
    *
    * @see isAttached()
    */
   const BoxLevel&
   getBoxLevel() const;

   /*!
    * @brief Whether the BoxLevelHandle is still attached to its
    * BoxLevel.
    */
   bool
   isAttached() const;

private:
   /*!
    * @brief Constructor to be called only by BoxLevel.
    *
    * This is the only constructor and it is private.  Only the
    * BoxLevel should allocate BoxLevelHandles.
    *
    * @param[in] box_level The BoxLevel to be attached to
    * this handle.
    */
   explicit BoxLevelHandle(
      const BoxLevel * box_level);

   /*!
    * @brief Forbidden copy constructor.
    *
    * This constructor is unimplemented and forbidden.  We never want
    * multiple handles attached to the same BoxLevel.
    */
   BoxLevelHandle(
      const BoxLevelHandle& other);

   /*!
    * @brief Forbidden assignment operator.
    *
    * This operation is unimplemented and forbidden.  We never want
    * multiple handles attached to the same BoxLevel.
    */
   BoxLevelHandle&
   operator = (
      const BoxLevelHandle& other);

   /*!
    * @brief Detach the BoxLevel
    *
    * To be called when the attached BoxLevel changes in a way
    * that can invalidate Connector data.
    *
    * Only the BoxLevel that is attached to the
    * BoxLevelHandle should call this method.
    */
   void
   detachMyBoxLevel();

   //@{
   /*!
    * @brief Allows BoxLevel to allocate BoxLevelHandles
    * and to call detachMyBoxLevel().
    */
   friend class BoxLevel;
   //@}

   /*!
    * @brief Pointer to the BoxLevel attached to this handle.
    */
   const BoxLevel* d_box_level;

};

}
}

#ifdef SAMRAI_INLINE
#include "SAMRAI/hier/BoxLevelHandle.I"
#endif

#endif // included_hier_BoxLevelHandle

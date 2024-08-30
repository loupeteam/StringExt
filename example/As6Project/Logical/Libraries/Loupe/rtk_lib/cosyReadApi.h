/*

Configuration System (COSY) read API.

Detailed description see cosyApi.h!

*/

#ifndef _COSY_READ_API_H_
#define _COSY_READ_API_H_

#include <cosyApi.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* COSY iterate flags */
enum COSY_ITERATE_FLAGS
{
	COSY_ITERATE_DEFAULT = 0, /* Iterate only members of the first level. */
	COSY_ITERATE_SUB_MEMBER = 1 /* Iterate all members of an element. Also sub members. */
};

/*
 * COSY iteration callback.
 *
 * Invoked for each existing configuration element. Elements must not be added
 * or removed during iteration.
 * context ........	user context.
 * hCosy	........... COSY element handle.
 *
 * Return true - continue iteration, false - stop iteration.
 */
typedef bool (*COSY_ITERATE_FP)(uintptr_t context, COSY_H hCosy);

/*
 * COSY element member iteration callback.
 *
 * Invoked for each existing member of an element. Members of the same level
 * must not be added or removed during iteration.
 * context ........	user context.
 * hCosy	........... COSY element handle.
 * id ............. member id.
 * elementType .... member type ("Group", "Property").
 *
 * Return true - continue iteration, false - stop iteration.
 */
typedef bool (*COSY_ITERATE_MEMBERS_FP)(uintptr_t context, COSY_H hCosy, const char* id, const char* memberType);

/*
 * Gets the location of a COSY element.
 *
 * Returns a pointer to the location string, NULL on failure.
 */
const char* cosyGetElementLocation(COSY_H hCosy);

/*
 * Gets the id of a COSY element.
 *
 * Returns a pointer to the id string, NULL on failure.
 */
const char* cosyGetElementId(COSY_H hCosy);

/*
 * Gets the type of a COSY element.
 *
 * Returns a pointer to the type string, NULL on failure.
 */
const char* cosyGetElementType(COSY_H hCosy);

/*
 * Gets the technology package of a COSY element.
 *
 * Returns a pointer to the technology package string, NULL on failure.
 */
const char* cosyGetElementTechnologyPackage(COSY_H hCosy);


/*
 * Tests if the COSY element has a non volatile copy.
 *
 * Return true if non volatile, false if volatile.
 */
bool cosyIsElementNonVolatile(COSY_H hCosy);

/*
 * Gets the value of a group.
 *
 * Returns a pointer to the value string of a group, NULL on failure or if no value is set.
 */
const char* cosyGetGroupValue(COSY_H hCosy, const char* id);

/*
 * Gets the IEC type of a property.
 *
 * Returns a pointer to the type string (IEC), NULL on failure or if no type is set.
 */
const char* cosyGetPropertyType(COSY_H hCosy, const char* id);

/*
 * Gets a property value.
 *
 * Also suceeeds if the specified bytes to read are less than the real size,
 * therefore also the size value should be checked.
 *
 * Type mapping (IEC -> type of the given value pointer):
 * BOOL          -> int
 * SINT          -> int
 * INT           -> int
 * DINT          -> int
 * USINT         -> int
 * UINT          -> int
 * UDINT         -> int
 * BYTE          -> int
 * WORD          -> int
 * DWORD         -> int
 * REAL          -> String
 * LREAL         -> String
 * STRING        -> String
 * TIME          -> String
 * DATE          -> String
 * DATE_AND_TIME -> String
 * TIME_OF_DAY   -> String
 * ULINT         -> not supported
 * LWORD         -> not supported
 * WSTRING       -> not supported
 * OCTET         -> not supported
 * LINT          -> not supported
 *
 * Return true if succeeds, false on failure.
 */
bool cosyGetPropertyValue(COSY_H hCosy, const char* id, const char* iecType, size_t bytesToRead, void* pValue,
                          size_t* pValueSize);

/*
 * Gets the size of a property.
 *
 * Return true if succeeds, false on failure.
 */
bool cosyGetPropertySize(COSY_H hCosy, const char* id, size_t* pValueSize);

/*
 * Iterates existing COSY elements.
 *
 * If a type is specified only elements of this type are iterated. Otherwise
 * all elements are iterated.
 *
 * Return true on success, false on failure.
 */
bool cosyIterateElements(COSY_ITERATE_FP fpIterate, uintptr_t context, const char* elementTypeFilter);

/*
 * Iterates COSY element members.
 *
 * If a start id is given (parameter startId), the iteration is done for the childs of
 * this member.
 *
 * Return true on success, false on failure.
 */
bool cosyIterateMembers(COSY_H hCosy, const char* startId, enum COSY_ITERATE_FLAGS flags,
                        COSY_ITERATE_MEMBERS_FP fpIterate, uintptr_t context);

/*
 * Tests if the COSY element has a non volatile copy which is different to the current
 * element configuration.
 *
 * Return true if dirty, false if not.
 */
bool cosyIsElementDirty(COSY_H hCosy);

/*
 * Gets the version of a COSY element.
 *
 * Returns a pointer to the version string, NULL on failure.
 */
const char* cosyGetElementVersion(COSY_H hCosy);


#if AR_CORE
#include <private/cosyReadApiP.h>
#endif

#ifdef __cplusplus
}
#endif

#endif

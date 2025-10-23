// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from base_interfaces:msg/Robot.idl
// generated code does not contain a copyright notice
#include "base_interfaces/msg/detail/robot__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
base_interfaces__msg__Robot__init(base_interfaces__msg__Robot * msg)
{
  if (!msg) {
    return false;
  }
  // v_x
  // v_y
  // v_omega
  return true;
}

void
base_interfaces__msg__Robot__fini(base_interfaces__msg__Robot * msg)
{
  if (!msg) {
    return;
  }
  // v_x
  // v_y
  // v_omega
}

bool
base_interfaces__msg__Robot__are_equal(const base_interfaces__msg__Robot * lhs, const base_interfaces__msg__Robot * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // v_x
  if (lhs->v_x != rhs->v_x) {
    return false;
  }
  // v_y
  if (lhs->v_y != rhs->v_y) {
    return false;
  }
  // v_omega
  if (lhs->v_omega != rhs->v_omega) {
    return false;
  }
  return true;
}

bool
base_interfaces__msg__Robot__copy(
  const base_interfaces__msg__Robot * input,
  base_interfaces__msg__Robot * output)
{
  if (!input || !output) {
    return false;
  }
  // v_x
  output->v_x = input->v_x;
  // v_y
  output->v_y = input->v_y;
  // v_omega
  output->v_omega = input->v_omega;
  return true;
}

base_interfaces__msg__Robot *
base_interfaces__msg__Robot__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Robot * msg = (base_interfaces__msg__Robot *)allocator.allocate(sizeof(base_interfaces__msg__Robot), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(base_interfaces__msg__Robot));
  bool success = base_interfaces__msg__Robot__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
base_interfaces__msg__Robot__destroy(base_interfaces__msg__Robot * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    base_interfaces__msg__Robot__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
base_interfaces__msg__Robot__Sequence__init(base_interfaces__msg__Robot__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Robot * data = NULL;

  if (size) {
    data = (base_interfaces__msg__Robot *)allocator.zero_allocate(size, sizeof(base_interfaces__msg__Robot), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = base_interfaces__msg__Robot__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        base_interfaces__msg__Robot__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
base_interfaces__msg__Robot__Sequence__fini(base_interfaces__msg__Robot__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      base_interfaces__msg__Robot__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

base_interfaces__msg__Robot__Sequence *
base_interfaces__msg__Robot__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Robot__Sequence * array = (base_interfaces__msg__Robot__Sequence *)allocator.allocate(sizeof(base_interfaces__msg__Robot__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = base_interfaces__msg__Robot__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
base_interfaces__msg__Robot__Sequence__destroy(base_interfaces__msg__Robot__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    base_interfaces__msg__Robot__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
base_interfaces__msg__Robot__Sequence__are_equal(const base_interfaces__msg__Robot__Sequence * lhs, const base_interfaces__msg__Robot__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!base_interfaces__msg__Robot__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
base_interfaces__msg__Robot__Sequence__copy(
  const base_interfaces__msg__Robot__Sequence * input,
  base_interfaces__msg__Robot__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(base_interfaces__msg__Robot);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    base_interfaces__msg__Robot * data =
      (base_interfaces__msg__Robot *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!base_interfaces__msg__Robot__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          base_interfaces__msg__Robot__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!base_interfaces__msg__Robot__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

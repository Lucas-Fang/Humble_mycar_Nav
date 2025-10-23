# generated from rosidl_generator_py/resource/_idl.py.em
# with input from base_interfaces:msg/Robot.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Robot(type):
    """Metaclass of message 'Robot'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interfaces.msg.Robot')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__robot
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__robot
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__robot
            cls._TYPE_SUPPORT = module.type_support_msg__msg__robot
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__robot

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Robot(metaclass=Metaclass_Robot):
    """Message class 'Robot'."""

    __slots__ = [
        '_v_x',
        '_v_y',
        '_v_omega',
    ]

    _fields_and_field_types = {
        'v_x': 'float',
        'v_y': 'float',
        'v_omega': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.v_x = kwargs.get('v_x', float())
        self.v_y = kwargs.get('v_y', float())
        self.v_omega = kwargs.get('v_omega', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.v_x != other.v_x:
            return False
        if self.v_y != other.v_y:
            return False
        if self.v_omega != other.v_omega:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def v_x(self):
        """Message field 'v_x'."""
        return self._v_x

    @v_x.setter
    def v_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'v_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'v_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._v_x = value

    @builtins.property
    def v_y(self):
        """Message field 'v_y'."""
        return self._v_y

    @v_y.setter
    def v_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'v_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'v_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._v_y = value

    @builtins.property
    def v_omega(self):
        """Message field 'v_omega'."""
        return self._v_omega

    @v_omega.setter
    def v_omega(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'v_omega' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'v_omega' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._v_omega = value

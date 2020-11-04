# jstruct

Map json tree to native cpp struct, provided the json follow a regular schema.

## Backgroud

There are so many json libs can used in C++, while not convenient for use more
or less.

This is not another json lib, but wrapper an underlying json lib, then convert
the json dmo to a native nested strut in C++, to make json operation easy to
read and write.

In current first solution, it is required manually write header file to define
a json dmo tree in C++ struct grammar, then a script (written in perl) is
aviable to generate the corresponding .cpp file, which can be complied along
with the actual project where use the json.

The next plan is devolopping another tool to generate both header and .cpp
file from json schema.

The underlying json lib is [rapidjson](https://github.com/Tencent/rapidjson)
which maybe has the best performance. It is not difficult to modify the
implementation to fit another json lib you prefered.

## Json Schema Limit

This lib is no designed to work with arbitrary json, it assumes the json will
follow some regular json schema.

* The whole json dom tree(root node) is an object.
* The keys(fields) in any object is determined, and should be a word that can
  be used as a valid identifier in C++ and not conflict with C++ keywords.
* The items in an array have the same type, scalar (number or string) or
  object with the same inner type.
* Only have one-dimension array, not support multi-dimension, say matrix or array
  of array.

It is easy to satisfy the requirement above in pratical project, especially
when need to design a json schema first.

## Json Struct in C++

Map json tree to C++ structure as following rules:

* json object is a struct, actually class with public fields by default, only
  two method that covert from and to json value in dmo, beside the basic
  construtor and destructor.
* object feild is a pointer member in C++ struct, which point to the actual
  struct.
* use `std::vector` to represent array in json.
* use `std::string` to represent string value in json.
* other scalar value is straightforward, such as bool and number. Json only
  has number, but json schema can define int or double and even define value
  range, so just select the appropriate numeric type in C++.

Some note:

* Though we can define json struct in C++98, best use modern C++ after C++11.
* Better to use namespace for each json dmo, since will define many inner
  structs for the json dmo.
* Use pointer member because usually in json often omit a whole sub-tree, so
  as to save memery. It is possible to use direct struct member, to avoid
  dynamic alloc, but that is another design.
* Use raw pointer not smart pointer in the inner struct, it is safe if provide
  destructor, which is desgined auto-generated.
* Provide default value for fileds in constructor, to handle the maybe omitted
  field in json. It is possible use `std::option` to handle such case, but may
  not necessary in most pratical project.

## Work Flow

Assume a common server program, to read a json request and write a json
response.

1. parse json string to json dmo, using rapidjson;
2. convert json dmo to json struct;
3. operate on json struct, in bussiness code;
4. convert json struct to json dmo;
5. serialize json dom to json string, using rapidjson.

## Usage and Example

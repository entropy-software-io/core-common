# Entropy Common Core Components
A collection of core utilities and containers used throughout Entropy Software products and projects.

## Customization

### Specifying custom link target
Set ```ENTROPY_CORE_EXTRA_INCLUDE_DIRECTORIES``` to a path where your custom header files are. 

Set ```ENTROPY_CORE_EXTRA_LINK_LIBRARIES``` for any custom libraries that will be linked. The core library builds into object files, so this is less necessary.

```
set (ENTROPY_CORE_EXTRA_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/MyApp/Include")
set (ENTROPY_CORE_EXTRA_LINK_LIBRARIES "MyLib")
```

### Allocator
Set ```ENTROPY_CORE_CUSTOM_ALLOCATOR``` to the type of your allocator. ```T``` is the data type to allocate.

```
set (ENTROPY_CORE_CUSTOM_ALLOCATOR "std::allocator<T>")
```

Set ```ENTROPY_CORE_CUSTOM_ALLOCATOR_INCLUDES``` add #include statements for your type.

```
set (ENTROPY_CORE_CUSTOM_ALLOCATOR_INCLUDES "#include \"Path/To/MyAllocator.h\"")
```

### String Type
A custom string type can be used throughout the code. Doing so requires implementing a ```StringOps``` struct containing specific static functions to translate operations. The struct must be in the ```Entropy``` namespace.

Set ```ENTROPY_CORE_CUSTOM_STRING_INCLUDES``` to the location of the header file that contains the struct definition.

```
set (ENTROPY_CORE_CUSTOM_STRING_INCLUDES "#include \"Path/To/MyString.h\"")
```

See ```Config/StringOps.h.in``` for the required API of the ```StringOps``` struct.

> [!NOTE]
> The StringOps structure is subject to change in the future.

### Vector Type
A custom vector (dynamically expandable array) type can be used throughout the code. Doing so requires implementing a ```VectorOps``` struct containing specific static functions to translate operations. The struct must be in the ```Entropy``` namespace.

Set ```ENTROPY_CORE_CUSTOM_VECTOR_INCLUDES``` to the location of the header file that contains the struct definition.

```
set (ENTROPY_CORE_CUSTOM_VECTOR_INCLUDES "#include \"Path/To/MyVector.h\"")
```

See ```Config/VectorOps.h.in``` for the required API of the ```VectorOps``` struct.

> [!NOTE]
> The VectorOps structure is subject to change in the future.

> [!NOTE]
> Your vector type should support iteration with begin() & end() similar to std::vector<>

### Map Type
A custom map type can be used throughout the code. Doing so requires implementing a ```MapOps``` struct containing specific static functions to translate operations. The struct must be in the ```Entropy``` namespace.

Set ```ENTROPY_CORE_CUSTOM_MAP_INCLUDES``` to the location of the header file that contains the struct definition.

```
set (ENTROPY_CORE_CUSTOM_MAP_INCLUDES "#include \"Path/To/MyMap.h\"")
```

See ```Config/MapOps.h.in``` for the required API of the ```MapOps``` struct.

> [!NOTE]
> The MapOps structure is subject to change in the future.

> [!NOTE]
> Your map type should support iteration with begin() & end() similar to std::map<>. The iterator must have ```first``` and ```second``` members.

### Function Type
Set ```ENTROPY_CORE_CUSTOM_FUNCTION``` to the type of your function. ```T``` is the function type to allocate.

```
set (ENTROPY_CORE_CUSTOM_FUNCTION "std::function<T>")
```

Set ```ENTROPY_CORE_CUSTOM_FUNCTION_INCLUDES``` add #include statements for your type.

```
set (ENTROPY_CORE_CUSTOM_FUNCTION_INCLUDES "#include \"Path/To/MyFunction.h\"")
```

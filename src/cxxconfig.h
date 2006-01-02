/*
  This is a little work around: if the C compiler does not support const
  "const" would be define as an empty string and this would not make the C++
  compiler work (where const is a keyword). So if const for C compiler does
  not work we still keep const for C++ compiler.
*/

#ifdef __cplusplus
#undef const 
#endif /* __cplusplus */

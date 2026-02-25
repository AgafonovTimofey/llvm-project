// RUN: %clang_cc1 -verify %s

int bar;
// expected-note@-1 4{{declared here}}

int foo()
{
  // FIXME: Bad error recovery.
  (void)(baz<> + baz<>);
  // expected-error@-1 2{{use of undeclared identifier 'baz'; did you mean 'bar'?}}
  // expected-error@-2 2{{'bar' is expected to be a non-type template, but instantiated to a class template}}
}

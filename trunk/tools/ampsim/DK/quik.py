#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# copied from https://github.com/avelino/quik
#
# copied license statement:
# -------------------------------------------------------------------------
# The MIT License (MIT)
#
# Copyright (c) 2013 Thiago Avelino
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# -------------------------------------------------------------------------
#
# Changed:
#  - replaced '#' character by '%' to make it work better with C++
#

import re, operator, os
try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO
    xrange = range


VERSION = (0, 2, 3)
VERSION_TAG = 'dev'

__version__ = ".".join(map(str, VERSION))
if VERSION_TAG:
    __version__ = "{0}-{1}".format(
        __version__, VERSION_TAG)


class Template:
    def __init__(self, content):
        self.content = content
        self.root_element = None

    def render(self, namespace, loader=None):
        output = StoppableStream()
        self.merge_to(namespace, output, loader)
        return output.getvalue()

    def ensure_compiled(self):
        if not self.root_element:
            self.root_element = TemplateBody(self.content)

    def merge_to(self, namespace, fileobj, loader=None):
        if loader is None:
            loader = NullLoader()
        self.ensure_compiled()
        self.root_element.evaluate(fileobj, namespace, loader)


class TemplateError(Exception):
    pass


class TemplateSyntaxError(TemplateError):
    def __init__(self, element, expected):
        self.element = element
        self.text_understood = element.full_text()[:element.end]
        self.line = 1 + self.text_understood.count('\n')
        self.column = len(self.text_understood) - self.text_understood.rfind('\n')
        got = element.next_text()
        if len(got) > 40:
            got = got[:36] + ' ...'
        Exception.__init__(self, "line %d, column %d: expected %s in %s, got: %s ..." % (self.line, self.column, expected, self.element_name(), got))

    def get_position_strings(self):
        error_line_start = 1 + self.text_understood.rfind('\n')
        if '\n' in self.element.next_text():
            error_line_end = self.element.next_text().find('\n') + self.element.end
        else:
            error_line_end = len(self.element.full_text())
        error_line = self.element.full_text()[error_line_start:error_line_end]
        caret_pos = self.column
        return [error_line, ' ' * (caret_pos - 1) + '^']

    def element_name(self):
        return re.sub('([A-Z])', lambda m: ' ' + m.group(1).lower(), self.element.__class__.__name__).strip()


class NullLoader:
    def load_text(self, name):
        raise TemplateError("no loader available for '%s'" % name)

    def load_template(self, name):
        raise self.load_text(name)


class FileLoader:
    def __init__(self, basedir, debugging=False):
        self.basedir = basedir
        self.known_templates = {}
        self.debugging = debugging
        if debugging:
            print("creating caching file loader with basedir: {0}".format(basedir))

    def filename_of(self, name):
        return os.path.join(self.basedir, name)

    def load_text(self, name):
        if self.debugging:
            print("Loading text from {0} {1}".format(self.basedir, name))
        f = open(self.filename_of(name))
        try:
            return f.read()
        finally:
            f.close()

    def load_template(self, name):
        if self.debugging:
            print("Loading template... {0}".format(name))

        mtime = os.path.getmtime(self.filename_of(name))
        if self.known_templates.get(name, None):
            template, prev_mtime = self.known_templates[name]
            if mtime <= prev_mtime:
                if self.debugging:
                    print("loading parsed template from cache")
                return template
        if self.debugging:
            print("loading text from disk")
        template = Template(self.load_text(name))
        template.ensure_compiled()
        self.known_templates[name] = (template, mtime)
        return template


class StoppableStream(StringIO):
    def __init__(self, buf=''):
        self.stop = False
        StringIO.__init__(self, buf)

    def write(self, s):
        if not self.stop:
            StringIO.write(self, s)


WHITESPACE_TO_END_OF_LINE = re.compile(r'[ \t\r]*\n(.*)', re.S)

class NoMatch(Exception): pass


class LocalNamespace(dict):
    def __init__(self, parent):
        dict.__init__(self)
        self.parent = parent

    def __getitem__(self, key):
        try: return dict.__getitem__(self, key)
        except KeyError:
            parent_value = self.parent[key]
            self[key] = parent_value
            return parent_value

    def top(self):
        if hasattr(self.parent, "top"):
            return self.parent.top()
        return self.parent

    def __repr__(self):
        return dict.__repr__(self) + '->' + repr(self.parent)


class _Element:
    def __init__(self, text, start=0):
        self._full_text = text
        self.start = self.end = start
        self.parse()

    def next_text(self):
        return self._full_text[self.end:]

    def my_text(self):
        return self._full_text[self.start:self.end]

    def full_text(self):
        return self._full_text

    def syntax_error(self, expected):
        return TemplateSyntaxError(self, expected)

    def identity_match(self, pattern):
        m = pattern.match(self._full_text, self.end)
        if not m: raise NoMatch()
        self.end = m.start(pattern.groups)
        return m.groups()[:-1]

    def next_match(self, pattern):
        m = pattern.match(self._full_text, self.end)
        if not m: return False
        self.end = m.start(pattern.groups)
        return m.groups()[:-1]

    def optional_match(self, pattern):
        m = pattern.match(self._full_text, self.end)
        if not m: return False
        self.end = m.start(pattern.groups)
        return True

    def require_match(self, pattern, expected):
        m = pattern.match(self._full_text, self.end)
        if not m: raise self.syntax_error(expected)
        self.end = m.start(pattern.groups)
        return m.groups()[:-1]

    def next_element(self, element_spec):
        if callable(element_spec):
            element = element_spec(self._full_text, self.end)
            self.end = element.end
            return element
        else:
            for element_class in element_spec:
                try: element = element_class(self._full_text, self.end)
                except NoMatch: pass
                else:
                    self.end = element.end
                    return element
            raise NoMatch()

    def require_next_element(self, element_spec, expected):
        if callable(element_spec):
            try: element = element_spec(self._full_text, self.end)
            except NoMatch: raise self.syntax_error(expected)
            else:
                self.end = element.end
                return element
        else:
            for element_class in element_spec:
                try: element = element_class(self._full_text, self.end)
                except NoMatch: pass
                else:
                    self.end = element.end
                    return element
            expected = ', '.join([cls.__name__ for cls in element_spec])
            raise self.syntax_error('one of: ' + expected)


class Text(_Element):
    PLAIN = re.compile(r'((?:[^\\\@%]+|\\[\@%])+|\@[^!\{a-z0-9_]|\@@|%@|%[^\{\}a-zA-Z0-9%\*]+|\\.)(.*)$', re.S + re.I)
    ESCAPED_CHAR = re.compile(r'\\([\\\@%])')

    def parse(self):
        text, = self.identity_match(self.PLAIN)
        def unescape(match):
            return match.group(1)
        self.text = self.ESCAPED_CHAR.sub(unescape, text)

    def evaluate(self, stream, namespace, loader):
        stream.write(self.text)


class FallthroughHashText(_Element):
    """ Plain tex, starting a hash, but which wouldn't be matched
        by a directive or a macro earlier.
        The canonical example is an HTML color spec.
        Another good example, is in-document hypertext links
        (or the dummy versions thereof often used a href targets
        when javascript is used.
        Note that it MUST NOT match block-ending directives. """
    # because of earlier elements, this will always start with a hash
    PLAIN = re.compile(r'(\%+\{?[\d\w]*\}?)(.*)$', re.S)

    def parse(self):
        self.text, = self.identity_match(self.PLAIN)
        if self.text.startswith('%end') or self.text.startswith('%{end}') or self.text.startswith('%else') or self.text.startswith('%{else}') or self.text.startswith('%elseif') or self.text.startswith('%{elseif}'):
            raise NoMatch

    def evaluate(self, stream, namespace, loader):
        stream.write(self.text)


class IntegerLiteral(_Element):
    INTEGER = re.compile(r'(-?\d+)(.*)', re.S)

    def parse(self):
        self.value, = self.identity_match(self.INTEGER)
        self.value = int(self.value)

    def calculate(self, namespace, loader):
        return self.value


class FloatingPointLiteral(_Element):
    FLOAT = re.compile(r'(-?\d+\.\d+)(.*)', re.S)

    def parse(self):
        self.value, = self.identity_match(self.FLOAT)
        self.value = float(self.value)

    def calculate(self, namespace, loader):
        return self.value


class BooleanLiteral(_Element):
    BOOLEAN = re.compile(r'((?:true)|(?:false))(.*)', re.S | re.I)

    def parse(self):
        self.value, = self.identity_match(self.BOOLEAN)
        self.value = self.value.lower() == 'true'

    def calculate(self, namespace, loader):
        return self.value


class StringLiteral(_Element):
    STRING = re.compile(r"'((?:\\['nrbt\\\\\\@]|[^'\\])*)'(.*)", re.S)
    ESCAPED_CHAR = re.compile(r"\\([nrbt'\\])")

    def parse(self):
        value, = self.identity_match(self.STRING)
        def unescape(match):
            return {'n': '\n', 'r': '\r', 'b': '\b', 't': '\t', '"': '"', '\\': '\\', "'": "'"}.get(match.group(1), '\\' + match.group(1))
        self.value = self.ESCAPED_CHAR.sub(unescape, value)

    def calculate(self, namespace, loader):
        return self.value

class InterpolatedStringLiteral(StringLiteral):
    STRING = re.compile(r'"((?:\\["nrbt\\\\\\@]|[^"\\])*)"(.*)', re.S)
    ESCAPED_CHAR = re.compile(r'\\([nrbt"\\])')

    def parse(self):
        StringLiteral.parse(self)
        self.block = Block(self.value, 0)

    def calculate(self, namespace, loader):
        output = StoppableStream()
        self.block.evaluate(output, namespace, loader)
        return output.getvalue()


class Range(_Element):
    MIDDLE = re.compile(r'([ \t]*\.\.[ \t]*)(.*)$', re.S)

    def parse(self):
        self.value1 = self.next_element((FormalReference, IntegerLiteral))
        self.identity_match(self.MIDDLE)
        self.value2 = self.next_element((FormalReference, IntegerLiteral))

    def calculate(self, namespace, loader):
        value1 = self.value1.calculate(namespace, loader)
        value2 = self.value2.calculate(namespace, loader)
        if value2 < value1:
            return xrange(value1, value2 - 1, -1)
        return xrange(value1, value2 + 1)


class ValueList(_Element):
    COMMA = re.compile(r'\s*,\s*(.*)$', re.S)

    def parse(self):
        self.values = []
        try: value = self.next_element(Value)
        except NoMatch:
            pass
        else:
            self.values.append(value)
            while self.optional_match(self.COMMA):
                value = self.require_next_element(Value, 'value')
                self.values.append(value)

    def calculate(self, namespace, loader):
        return [value.calculate(namespace, loader) for value in self.values]


class _EmptyValues:
    def calculate(self, namespace, loader):
        return []


class ArrayLiteral(_Element):
    START = re.compile(r'\[[ \t]*(.*)$', re.S)
    END =   re.compile(r'[ \t]*\](.*)$', re.S)
    values = _EmptyValues()

    def parse(self):
        self.identity_match(self.START)
        try:
            self.values = self.next_element((Range, ValueList))
        except NoMatch:
            pass
        self.require_match(self.END, ']')
        self.calculate = self.values.calculate

class DictionaryLiteral(_Element):
    START = re.compile(r'{[ \t]*(.*)$', re.S)
    END =   re.compile(r'[ \t]*}(.*)$', re.S)
    KEYVALSEP = re.compile(r'[ \t]*:[[ \t]*(.*)$', re.S)
    PAIRSEP = re.compile(r'[ \t]*,[ \t]*(.*)$', re.S)

    def parse(self):
        self.identity_match(self.START)
        self.local_data = {}
        if self.optional_match(self.END):
            # it's an empty dictionary
            return
        while(True):
            key = self.next_element(Value)
            self.require_match(self.KEYVALSEP, ':')
            value = self.next_element(Value)
            self.local_data[key] = value
            if not self.optional_match(self.PAIRSEP): break
        self.require_match(self.END, '}')

    # Note that this delays calculation of values until it's used.
    # TODO confirm that that's correct.
    def calculate(self, namespace, loader):
        tmp = {}
        for (key,val) in self.local_data.items():
            tmp[key.calculate(namespace, loader)] = val.calculate(namespace, loader)
        return tmp


class Value(_Element):
    def parse(self):
        self.expression = self.next_element((FormalReference, FloatingPointLiteral, IntegerLiteral,
                                             StringLiteral, InterpolatedStringLiteral, ArrayLiteral,
                                             DictionaryLiteral, ParenthesizedExpression, UnaryOperatorValue,
                                             BooleanLiteral))

    def calculate(self, namespace, loader):
        return self.expression.calculate(namespace, loader)


class NameOrCall(_Element):
    NAME = re.compile(r'([a-zA-Z0-9_]+)(.*)$', re.S)
    parameters = None

    def parse(self):
        self.name, = self.identity_match(self.NAME)
        try: self.parameters = self.next_element(ParameterList)
        except NoMatch: pass

    def calculate(self, current_object, loader, top_namespace):
        look_in_dict = True
        if not isinstance(current_object, LocalNamespace):
            try:
                result = getattr(current_object, self.name)
                look_in_dict = False
            except AttributeError:
                pass
        if look_in_dict:
            try: result = current_object[self.name]
            except KeyError: result = None
            except TypeError: result = None
            except AttributeError: result = None
        if result is None:
            return None ## TODO: an explicit 'not found' exception?
        if self.parameters is not None:
            result = result(*self.parameters.calculate(top_namespace, loader))
        return result


class SubExpression(_Element):
    DOT = re.compile('\.(.*)', re.S)

    def parse(self):
        self.identity_match(self.DOT)
        self.expression = self.next_element(VariableExpression)

    def calculate(self, current_object, loader, global_namespace):
        return self.expression.calculate(current_object, loader, global_namespace)


class VariableExpression(_Element):
    subexpression = None

    def parse(self):
        self.part = self.next_element(NameOrCall)
        try: self.subexpression = self.next_element(SubExpression)
        except NoMatch: pass

    def calculate(self, namespace, loader, global_namespace=None):
        if global_namespace is None:
            global_namespace = namespace
        value = self.part.calculate(namespace, loader, global_namespace)
        if self.subexpression:
            value = self.subexpression.calculate(value, loader, global_namespace)
        return value


class ParameterList(_Element):
    START = re.compile(r'\(\s*(.*)$', re.S)
    COMMA = re.compile(r'\s*,\s*(.*)$', re.S)
    END = re.compile(r'\s*\)(.*)$', re.S)
    values = _EmptyValues()

    def parse(self):
        self.identity_match(self.START)
        try: self.values = self.next_element(ValueList)
        except NoMatch: pass
        self.require_match(self.END, ')')

    def calculate(self, namespace, loader):
        return self.values.calculate(namespace, loader)


class FormalReference(_Element):
    START = re.compile(r'\@(!?)(\{?)(.*)$', re.S)
    CLOSING_BRACE = re.compile(r'\}(.*)$', re.S)

    def parse(self):
        self.silent, braces = self.identity_match(self.START)
        self.expression = self.require_next_element(VariableExpression, 'expression')
        if braces: self.require_match(self.CLOSING_BRACE, '}')
        self.calculate = self.expression.calculate

    def evaluate(self, stream, namespace, loader):
        value = self.expression.calculate(namespace, loader)
        if value is None:
            if self.silent: value = ''
            else: value = self.my_text()

        try:
            basestring
            def is_string(s):
                return isinstance(s, basestring)
        except NameError:
            def is_string(s):
                return type(s) == type('')

        if is_string(value):
            stream.write(value)
        else:
            stream.write(str(value))


class Null:
    def evaluate(self, stream, namespace, loader): pass


class Comment(_Element, Null):
    COMMENT = re.compile('%(?:%.*?(?:\n|$)|\*.*?\*%(?:[ \t]*\n)?)(.*)$', re.M + re.S)

    def parse(self):
        self.identity_match(self.COMMENT)


def boolean_value(variable_value):
    if variable_value == False:
        return False
    return not (variable_value is None)


class BinaryOperator(_Element):

    BINARY_OP = re.compile(r'\s*(>=|<=|<|==|!=|>|%|\|\||&&|or|and|\+|\-|\*|\/|\%)\s*(.*)$', re.S)
    try:
        operator.__gt__
    except AttributeError:
        operator.__gt__ = lambda a, b: a > b
        operator.__lt__ = lambda a, b: a < b
        operator.__ge__ = lambda a, b: a >= b
        operator.__le__ = lambda a, b: a <= b
        operator.__eq__ = lambda a, b: a == b
        operator.__ne__ = lambda a, b: a != b
        operator.mod = lambda a, b: a % b

    OPERATORS = {
        '>': operator.gt,
        '>=': operator.ge,
        '<': operator.lt,
        '<=': operator.le,
        '==': operator.eq,
        '!=': operator.ne,
        '%': operator.mod,
        '||': lambda a,b : boolean_value(a) or boolean_value(b),
        '&&': lambda a,b : boolean_value(a) and boolean_value(b),
        'or': lambda a,b : boolean_value(a) or boolean_value(b),
        'and': lambda a,b : boolean_value(a) and boolean_value(b),
        '+' : operator.add,
        '-' : operator.sub,
        '/' : lambda a, b: a / b,
        '*' : operator.mul}
    PRECEDENCE = {
        '>': 2,
        '<': 2,
        '==': 2,
        '>=': 2,
        '<=': 2,
        '!=': 2,
        '||': 1,
        '&&': 1,
        'or': 1,
        'and': 1,
        '+': 3,
        '-': 3,
        '*': 3,
        '/': 3,
        '%': 3}

    def parse(self):
        op_string, = self.identity_match(self.BINARY_OP)
        self.apply_to = self.OPERATORS[op_string]
        self.precedence = self.PRECEDENCE[op_string]

    def greater_precedence_than(self, other):
        return self.precedence > other.precedence


class UnaryOperatorValue(_Element):
    UNARY_OP = re.compile(r'\s*(!)\s*(.*)$', re.S)
    OPERATORS = {'!': operator.__not__}
    def parse(self):
        op_string, = self.identity_match(self.UNARY_OP)
        self.value = self.next_element(Value)
        self.op = self.OPERATORS[op_string]

    def calculate(self, namespace, loader):
        return self.op(self.value.calculate(namespace, loader))


class Expression(_Element):

    def parse(self):
        self.expression = [self.next_element(Value)]
        while(True):
            try:
                binary_operator = self.next_element(BinaryOperator)
                value = self.require_next_element(Value, 'value')
                self.expression.append(binary_operator)
                self.expression.append(value)
            except NoMatch:
                break

    def calculate(self, namespace, loader):
        if not self.expression or len(self.expression) == 0:
            return False
        #TODO: how does velocity deal with an empty condition expression?

        opstack = []
        valuestack = [self.expression[0]]
        terms = self.expression[1:]

        # use top of opstack on top 2 values of valuestack
        def stack_calculate(ops, values, namespace, loader):
            value2 = values.pop()
            if isinstance(value2, Value):
                value2 = value2.calculate(namespace, loader)
            value1 = values.pop()
            if isinstance(value1, Value):
                value1 = value1.calculate(namespace, loader)
            result = ops.pop().apply_to(value1, value2)
            # TODO this doesn't short circuit -- does velocity?
            # also note they're eval'd out of order
            values.append(result)

        while terms:
            # next is a binary operator
            if not opstack or terms[0].greater_precedence_than(opstack[-1]):
                opstack.append(terms[0])
                valuestack.append(terms[1])
                terms = terms[2:]
            else:
                stack_calculate(opstack, valuestack, namespace, loader)

        # now clean out the stacks
        while opstack:
            stack_calculate(opstack, valuestack, namespace, loader)

        if len(valuestack) != 1:
            print("evaluation of expression in Condition.calculate is messed up: final length of stack is not one")
            #TODO handle this officially

        result = valuestack[0]
        if isinstance(result, Value):
            result = result.calculate(namespace, loader)
        return result


class ParenthesizedExpression(_Element):
    START = re.compile(r'\(\s*(.*)$', re.S)
    END = re.compile(r'\s*\)(.*)$', re.S)

    def parse(self):
        self.identity_match(self.START)
        expression = self.next_element(Expression)
        self.require_match(self.END, ')')
        self.calculate = expression.calculate


class Condition(_Element):
    def parse(self):
        expression = self.next_element(ParenthesizedExpression)
        self.optional_match(WHITESPACE_TO_END_OF_LINE)
        self.calculate = expression.calculate
        # TODO do I need to do anything else here?


class End(_Element):
    END = re.compile(r'%(?:end|{end})(.*)', re.I + re.S)

    def parse(self):
        self.identity_match(self.END)
        self.optional_match(WHITESPACE_TO_END_OF_LINE)


class ElseBlock(_Element):
    START = re.compile(r'%(?:else|{else})(.*)$', re.S + re.I)

    def parse(self):
        self.identity_match(self.START)
        self.block = self.require_next_element(Block, 'block')
        self.evaluate = self.block.evaluate


class ElseifBlock(_Element):
    START = re.compile(r'%elseif\b\s*(.*)$', re.S + re.I)

    def parse(self):
        self.identity_match(self.START)
        self.condition = self.require_next_element(Condition, 'condition')
        self.block = self.require_next_element(Block, 'block')
        self.calculate = self.condition.calculate
        self.evaluate = self.block.evaluate


class IfDirective(_Element):
    START = re.compile(r'%if\b\s*(.*)$', re.S + re.I)
    else_block = Null()

    def parse(self):
        self.identity_match(self.START)
        self.condition = self.next_element(Condition)
        self.block = self.require_next_element(Block, "block")
        self.elseifs = []
        while True:
            try: self.elseifs.append(self.next_element(ElseifBlock))
            except NoMatch: break
        try: self.else_block = self.next_element(ElseBlock)
        except NoMatch: pass
        self.require_next_element(End, '%else, %elseif or %end')

    def evaluate(self, stream, namespace, loader):
        if self.condition.calculate(namespace, loader):
            self.block.evaluate(stream, namespace, loader)
        else:
            for elseif in self.elseifs:
                if elseif.calculate(namespace, loader):
                    elseif.evaluate(stream, namespace, loader)
                    return
            self.else_block.evaluate(stream, namespace, loader)


class Assignment(_Element):
    START = re.compile(r'\s*\@([a-z_][a-z0-9_]*(?:\.[a-z_][a-z0-9_]*)*)\s*=\s*(.*)$', re.S + re.I)
    END = re.compile(r'\s*\:(?:[ \t]*\r?\n)?(.*)$', re.S + re.M)

    def parse(self):
        var_name, = self.identity_match(self.START)
        self.terms = var_name.split('.')
        self.value = self.require_next_element(Expression, "expression")
        self.require_match(self.END, ')')

    def evaluate(self, stream, namespace, loader):
        thingy = namespace
        for term in self.terms[0:-1]:
            if thingy == None: return
            look_in_dict = True
            if not isinstance(thingy, LocalNamespace):
                try:
                    thingy = getattr(thingy, term)
                    look_in_dict = False
                except AttributeError:
                    pass
            if look_in_dict:
                try:
                    thingy = thingy[term]
                except KeyError: thingy = None
                except TypeError: thingy = None
                except AttributeError: thingy = None
        if thingy is not None:
            thingy[self.terms[-1]] = self.value.calculate(namespace, loader)

class MacroDefinition(_Element):
    START = re.compile(r'%macro\b(.*)', re.S + re.I)
    OPEN_PAREN = re.compile(r'[ \t]\s*(.*)$', re.S)
    NAME = re.compile(r'\s*([a-z][a-z_0-9]*)\b(.*)', re.S + re.I)
    CLOSE_PAREN = re.compile(r'[ \t]*\:(.*)$', re.S)
    ARG_NAME = re.compile(r'[, \t]+\@([a-z][a-z_0-9]*)(.*)$', re.S + re.I)
    RESERVED_NAMES = ('if', 'else', 'elseif', 'set', 'macro',
                      'for', 'parse', 'include', 'stop', 'end')
    def parse(self):
        self.identity_match(self.START)
        self.require_match(self.OPEN_PAREN, '(')
        self.macro_name, = self.require_match(self.NAME, 'macro name')
        if self.macro_name.lower() in self.RESERVED_NAMES:
            raise self.syntax_error('non-reserved name')
        self.arg_names = []
        while True:
            m = self.next_match(self.ARG_NAME)
            if not m: break
            self.arg_names.append(m[0])
        self.require_match(self.CLOSE_PAREN, ') or arg name')
        self.optional_match(WHITESPACE_TO_END_OF_LINE)
        self.block = self.require_next_element(Block, 'block')
        self.require_next_element(End, 'block')

    def evaluate(self, stream, namespace, loader):
        global_ns = namespace.top()
        macro_key = '%' + self.macro_name.lower()
        if global_ns.get(macro_key, None):
            raise Exception("cannot redefine macro")
        global_ns[macro_key] = self

    def execute_macro(self, stream, namespace, arg_value_elements, loader):
        if len(arg_value_elements) != len(self.arg_names):
            raise Exception("expected %d arguments, got %d" % (len(self.arg_names), len(arg_value_elements)))
        macro_namespace = LocalNamespace(namespace)
        for arg_name, arg_value in zip(self.arg_names, arg_value_elements):
            macro_namespace[arg_name] = arg_value.calculate(namespace, loader)
        self.block.evaluate(stream, macro_namespace, loader)


class MacroCall(_Element):
    START = re.compile(r'%([a-z][a-z_0-9]*)\b(.*)', re.S + re.I)
    OPEN_PAREN = re.compile(r'[ \t]\s*(.*)$', re.S)
    CLOSE_PAREN = re.compile(r'[ \t]*\:(.*)$', re.S)
    SPACE_OR_COMMA = re.compile(r'[ \t]*(?:,|[ \t])[ \t]*(.*)$', re.S)

    def parse(self):
        macro_name, = self.identity_match(self.START)
        self.macro_name = macro_name.lower()
        self.args = []
        if self.macro_name in MacroDefinition.RESERVED_NAMES or self.macro_name.startswith('end'):
            raise NoMatch()
        if not self.optional_match(self.OPEN_PAREN):
            # It's not really a macro call,
            # it's just a spare pound sign with text after it,
            # the typical example being a color spec: "#ffffff"
            # call it not-a-match and then let another thing catch it
            raise NoMatch()
        while True:
            try: self.args.append(self.next_element(Value))
            except NoMatch: break
            if not self.optional_match(self.SPACE_OR_COMMA): break
        self.require_match(self.CLOSE_PAREN, 'argument value or )')

    def evaluate(self, stream, namespace, loader):
        try: macro = namespace['%' + self.macro_name]
        except KeyError: raise Exception('no such macro: ' + self.macro_name)
        macro.execute_macro(stream, namespace, self.args, loader)


class IncludeDirective(_Element):
    START = re.compile(r'%include\b(.*)', re.S + re.I)
    OPEN_PAREN = re.compile(r'[ \t]*\(\s*(.*)$', re.S)
    CLOSE_PAREN = re.compile(r'[ \t]*\)(.*)$', re.S)

    def parse(self):
        self.identity_match(self.START)
        self.require_match(self.OPEN_PAREN, '(')
        self.name = self.require_next_element((StringLiteral, InterpolatedStringLiteral, FormalReference), 'template name')
        self.require_match(self.CLOSE_PAREN, ')')

    def evaluate(self, stream, namespace, loader):
        stream.write(loader.load_text(self.name.calculate(namespace, loader)))


class ParseDirective(_Element):
    START = re.compile(r'%parse\b(.*)', re.S + re.I)
    OPEN_PAREN = re.compile(r'[ \t]*\(\s*(.*)$', re.S)
    CLOSE_PAREN = re.compile(r'[ \t]*\)(.*)$', re.S)

    def parse(self):
        self.identity_match(self.START)
        self.require_match(self.OPEN_PAREN, '(')
        self.name = self.require_next_element((StringLiteral, InterpolatedStringLiteral, FormalReference), 'template name')
        self.require_match(self.CLOSE_PAREN, ')')

    def evaluate(self, stream, namespace, loader):
        template = loader.load_template(self.name.calculate(namespace, loader))
        ## TODO: local namespace?
        template.merge_to(namespace, stream, loader=loader)


class StopDirective(_Element):
    STOP = re.compile(r'%stop\b(.*)', re.S + re.I)

    def parse(self):
        self.identity_match(self.STOP)

    def evaluate(self, stream, namespace, loader):
        if hasattr(stream, 'stop'):
            stream.stop = True


# Represents a SINGLE user-defined directive
class UserDefinedDirective(_Element):
    DIRECTIVES = []

    def parse(self):
        self.directive = self.next_element(self.DIRECTIVES)

    def evaluate(self, stream, namespace, loader):
        self.directive.evaluate(stream, namespace, loader)


class SetDirective(_Element):
    START = re.compile(r'%set\b(.*)', re.S + re.I)

    def parse(self):
        self.identity_match(self.START)
        self.assignment = self.require_next_element(Assignment, 'assignment')

    def evaluate(self, stream, namespace, loader):
        self.assignment.evaluate(stream, namespace, loader)


class ForDirective(_Element):
    START = re.compile(r'%for\b(.*)$', re.S + re.I)
    OPEN_PAREN = re.compile(r'[ \t]\s*(.*)$', re.S)
    IN = re.compile(r'[ \t]+in[ \t]+(.*)$', re.S)
    LOOP_VAR_NAME = re.compile(r'\@([a-z_][a-z0-9_]*)(.*)$', re.S + re.I)
    CLOSE_PAREN = re.compile(r'[ \t]*\:(.*)$', re.S)

    def parse(self):
        ## Could be cleaner b/c syntax error if no '('
        self.identity_match(self.START)
        self.require_match(self.OPEN_PAREN, '(')
        self.loop_var_name, = self.require_match(self.LOOP_VAR_NAME, 'loop var name')
        self.require_match(self.IN, 'in')
        self.value = self.next_element(Value)
        self.require_match(self.CLOSE_PAREN, ')')
        self.block = self.next_element(Block)
        self.require_next_element(End, '%end')

    def evaluate(self, stream, namespace, loader):
        iterable = self.value.calculate(namespace, loader)
        counter = 1
        try:
            if iterable is None:
                return
            if hasattr(iterable, 'keys'): iterable = iterable.keys()
            if not hasattr(iterable, '__getitem__'):
                raise ValueError("value for @%s is not iterable in %%for: %s" % (self.loop_var_name, iterable))
            for item in iterable:
                namespace = LocalNamespace(namespace)
                namespace['velocityCount'] = counter
                namespace['velocityHasNext'] = counter < len(iterable)
                namespace[self.loop_var_name] = item
                self.block.evaluate(stream, namespace, loader)
                counter += 1
        except TypeError:
            raise


class TemplateBody(_Element):
    def parse(self):
        self.block = self.next_element(Block)
        if self.next_text():
            raise self.syntax_error('block element')

    def evaluate(self, stream, namespace, loader):
        namespace = LocalNamespace(namespace)
        self.block.evaluate(stream, namespace, loader)


class Block(_Element):
    def parse(self):
        self.children = []
        while True:
            try: self.children.append(self.next_element((Text, FormalReference, Comment, IfDirective, SetDirective,
                                                         ForDirective, IncludeDirective, ParseDirective,
                                                         MacroDefinition, StopDirective, UserDefinedDirective,
                                                         MacroCall, FallthroughHashText)))
            except NoMatch: break

    def evaluate(self, stream, namespace, loader):
        for child in self.children:
            child.evaluate(stream, namespace, loader)

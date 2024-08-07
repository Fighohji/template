import sys
import os
import io
from collections import defaultdict

from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrapped(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to
    return wrapped


input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

Ans = []


sys.stdout.write("\n".join(map(str, Ans)))

#!/usr/bin/python

import sys, os
from pprint import pprint

vector_scalar_ops = [('add', '+'),
                     ('sub', '-'),
                     ('mul', '*'),
                     ('div', '/')]

for (name,op) in vector_scalar_ops:
    os.system("./replace.py ssop.cui s%s.cu op=%s tex_knl_name=kamasu_vector_%s_tex_knl "
              "gld_knl_name=kamasu_vector_%s_gld_knl "
              "api_name=kamasu_vector_scalar_%s" % (name, op, name, name, name))
    os.system("./replace.py saxpy.cui vector_vector_%s.cu "
              "op=%s tex_knl_name=kamasu_vector_vector_%s_tex_knl "
              "gld_knl_name=kamasu_vector_vector_%s_gld_knl "
              "api_name=kamasu_vector_vector_%s" % (name, op, name, name, name))

    







                  



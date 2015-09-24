from __future__ import absolute_import, division, print_function, \
        unicode_literals

from nlp.libnlp import get_global_PTB_config
from nlp.ez import tokenize
import nlp.pipeline as pipeline
from nlp.pipeline import Pipeline

"""This module does natural language processing."""

__all__ = ["tokenize", "get_global_PTB_config", "pipeline", "Pipeline"]

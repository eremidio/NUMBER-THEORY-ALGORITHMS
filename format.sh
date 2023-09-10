#!/bin/env bash

find . -regex '.*\.\(cpp\|hpp\|c\|h\)' -exec clang-format -style=GNU -i "{}" \+

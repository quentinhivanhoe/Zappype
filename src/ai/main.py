#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## Zappype
## File description:
## main
##

import sys

import src.ai.ai

if __name__ == "__main__":
    try:
        src.ai.ai.process_ai()
    except Exception as e:
        print(e)
        exit(84)
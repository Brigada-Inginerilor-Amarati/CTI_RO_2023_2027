package org.paul.factories

class UnknownCarPartException : Exception {
    constructor(partName: String) : super("Unknown car part: $partName")
}
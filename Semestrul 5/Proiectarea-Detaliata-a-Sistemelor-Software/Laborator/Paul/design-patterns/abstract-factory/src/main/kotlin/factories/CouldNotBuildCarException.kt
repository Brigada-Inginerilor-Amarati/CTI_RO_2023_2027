package org.paul.factories

class CouldNotBuildCarException : Exception {
    constructor(reason: String) : super("Could not build car: $reason")
}
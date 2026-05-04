PROGRAM HelloWorld
DATA
    DEFINE message AS TEXT = "Hello, neuro world"
LOGIC
    // INTENTION:
    // Show a greeting on screen

    // CONTRACT:
    // - message must not be empty

    IF message = "" THEN
        ERROR "Empty message"
    END_IF

    SHOW message
END

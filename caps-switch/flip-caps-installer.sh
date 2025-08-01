#!/bin/bash

OS=$(uname)
SHELL_NAME=$(basename "$SHELL")

if [[ "$OS" == "Linux" || "$OS" == "Darwin" ]]; then
    if [[ "$SHELL_NAME" == "zsh" ]]; then

        cat << 'EOF' >> ~/.zshrc

# --- Ctrl+T Flip Case Toggle (Zsh) ---
function flip_case() {
    BUFFER=$(echo "$BUFFER" | tr 'a-zA-Z' 'A-Za-z')
    zle reset-prompt
}
zle -N flip_case
bindkey '^T' flip_case
# --- End Flip Case ---
EOF

        echo "Flip caps setup. Restart your terminal or run: source ~/.zshrc. ctrl + t will then flip case."

    elif [[ "$SHELL_NAME" == "bash" ]]; then

        cat << 'EOF' >> ~/.bashrc

# --- Ctrl+T Flip Last Command Case (Bash) ---
flip_case() {
    TMPFILE=$(mktemp)
    fc -ln 0 > "$TMPFILE" # Get last command

    tr 'A-Za-z' 'a-zA-Z' < "$TMPFILE" > "$TMPFILE.flipped"
    mv "$TMPFILE.flipped" "$TMPFILE"

    FLIPPED_COMMAND=$(<"$TMPFILE")
    # Remove any leading/trailing whitespace just in case
    FLIPPED_COMMAND="${FLIPPED_COMMAND#"${FLIPPED_COMMAND%%[![:space:]]*}"}"
    FLIPPED_COMMAND="${FLIPPED_COMMAND%"${FLIPPED_COMMAND##*[![:space:]]}"}"

    READLINE_LINE="$FLIPPED_COMMAND"
    READLINE_POINT=${#READLINE_LINE}

    rm "$TMPFILE"
}
bind -x '"\C-t":flip_case'
# --- End Flip Case ---
EOF

        echo "Supports version Bash 4.0+"
        echo "Flip caps setup. Restart your terminal or run: \"source ~/.bashrc\". ctrl + t will then flip case."

    else
        echo "Unsupported shell: $SHELL_NAME"
    fi

elif [[ "$OS" =~ "MINGW" || "$OS" =~ "CYGWIN" ]]; then

    echo "Powershell/Windows is not supported at the moment."

else
    echo "Unsupported OS: $OS"
fi

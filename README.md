# ClassPad System UI for Hollyhock 3

## About
This is an early test for accessing the Peg components in Hollyhock 3.  
### All addresses are currently hardcoded. **Only OS 7002 and 2000** are currently supported.

## How to Setup
1. Clone to project
2. Enter the devcontainer
3. `make compile_commands.json` or use the vscode task
4. Restart clangd (eg. via CRTL+SHIFT+P in vscode)

## How to build
```sh
# Build for OS 2000
make OS=2000

# Build for OS 7002
make OS=7002
```

Or execute the default vscode build task with CRTL+SHIFT+B

## How to use
The headers and libs are distributed in `dist/<OS>/` or in the archive `dist/systemui-<OS>.tar.gz`

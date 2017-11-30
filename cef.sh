#!/bin/sh

echo "-> NervSeed: CEF build tools"

# CEF Build dir: this is the root folder where CEF is built:
_cef_build_dir="/cygdrive/d/Projects/CEFBuild"

# CEF patch dir: this is the folder containing all the updated files required to build
# our patched version of CEF (with support for the Direct rendering to Direct3D)
_cef_patch_dir="`nv_get_project_dir`/deps/patches/cef"

nv_cef_call_python() {
  local PREVPATH=$PATH
  local pythonPath="$_cef_build_dir/depot_tools/win_tools-2_7_6_bin/python/bin"
  local toolsPath="$_cef_build_dir/depot_tools"
  export PATH="$pythonPath:$pythonPath/Scripts:$toolsPath:$PATH"
  $pythonPath/python.exe "$@"
  export PATH="$PREVPATH"
}

nv_cef_call_ninja() {
  local PREVPATH=$PATH
  local pythonPath="$_cef_build_dir/depot_tools/win_tools-2_7_6_bin/python/bin"
  local toolsPath="$_cef_build_dir/depot_tools"
  export PATH="$pythonPath:$pythonPath/Scripts:$toolsPath:$PATH"
  $toolsPath/ninja.exe "$@"
  export PATH="$PREVPATH"
}

# Initial setup of the CEF build folder.
nv_cef_setup() {
  # Copy the automate-git file:
  cp -f $_cef_patch_dir/automate-git.py $_cef_build_dir/automate/

  # Should also extract the depot tools from here.

  # This function is incomplete ! The initial deployment was in fact done manually
}

nv_cef_init_exports() {
  export CEF_USE_GN="1"
  # export GN_DEFINES="is_win_fastlink=true"
  export GN_DEFINES=""
  export GN_ARGUMENTS="--ide=vs2015 --sln=cef --filters=//cef/*"
}

# Update of the CEF sources to a given branch
nv_cef_update() {

  local branch="3163"
  nv_cef_init_exports

  local bdir=`cygpath -w "$_cef_build_dir"`
  # echo "using build dir: $bdir"
  cd "$_cef_build_dir/chromium_git"

  nv_cef_call_python ../automate/automate-git.py --download-dir=$bdir/chromium_git --depot-tools-dir=$bdir/depot_tools --no-distrib --no-build --branch=$branch

  cd - > /dev/null
}

# create the cef projects:
nv_cef_create_project() {
  nv_cef_init_exports

  # Copy all the updated files:
  cp -Rf "$_cef_patch_dir/src" "$_cef_build_dir/chromium_git/chromium/"

  # Once we are done copying the files ensure we call the translator tool:
  cd "$_cef_build_dir/chromium_git/chromium/src/cef/tools"
  nv_cef_call_python translator.py --root-dir ..
  cd - > /dev/null

  # Update the command buffer functions:
  cd "$_cef_build_dir/chromium_git/chromium/src"
  nv_cef_call_python "gpu\\command_buffer\\build_gles2_cmd_buffer.py"
  cd - > /dev/null

  # Create the project files:
  cd "$_cef_build_dir/chromium_git/chromium/src/cef"
  nv_cef_call_python tools/gclient_hook.py
  cd - > /dev/null
}

# build the cef library:
nv_cef_build() {
  nv_cef_init_exports
  
  local btype=${1:-Release}
  cd "$_cef_build_dir/chromium_git/chromium/src"
  nv_cef_call_ninja -C "out\\${btype}_GN_x64" cef

  echo "Done building CEF"
  cd - > /dev/null
}

# Make CEF distrib:
nv_cef_make_distrib() {
  #  cf. https://bitbucket.org/chromiumembedded/cef/wiki/BranchesAndBuilding.md
  local vsdir=`nv_get_visualstudio_dir`
  vsdir=`nv_to_win_path $vsdir`
  export CEF_VCVARS="$vsdir\\VC\\bin\\amd64\\vcvars64.bat"

  cd "$_cef_build_dir/chromium_git/chromium/src/cef/tools"

  nv_cef_call_python make_distrib.py --output-dir ../binary_distrib/ --ninja-build --x64-build --allow-partial

  echo "Done packaging CEF"
  cd - > /dev/null
}
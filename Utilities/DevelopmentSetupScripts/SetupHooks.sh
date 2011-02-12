#!/usr/bin/env bash
#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/


# Run this script to set up the git hooks for committing changes to ITK.
# For more information, see:
#   http://www.itk.org/Wiki/ITK/Git#Hooks
#   http://www.itk.org/Wiki/Git/Hooks


die() {
	echo 'failure during hook setup' 1>&2
	echo '-------------------------' 1>&2
	echo '' 1>&2
	echo "$@" 1>&2
	exit 1
}

u=$(cd "$(echo "$0"|sed 's/[^/]*$//')"; pwd)
cd "$u/../../.git/hooks"

# We need to have a git repository to do a pull.
if ! test -d ./.git; then
  git init || die "Could not run git init."
fi

# Grab the hooks.
# Use the local hooks if possible.
echo "Pulling the hooks..."
if GIT_DIR=.. git for-each-ref refs/remotes/origin/hooks 2>/dev/null | \
  grep -q '\<refs/remotes/origin/hooks$'; then
  git pull .. remotes/origin/hooks
else
  git pull http://public.kitware.com/ITKApps.git hooks || die "Downloading the hooks failed."
fi
cd ../..

# Set up hook chaining.
echo "Setting up ITK hook chaining: prepare-commit-msg, commit-msg, pre-commit"
git config hooks.chain-prepare-commit-msg Utilities/Hooks/prepare-commit-msg
git config hooks.chain-commit-msg Utilities/Hooks/commit-msg
git config hooks.chain-pre-commit Utilities/Hooks/pre-commit

echo "Done."

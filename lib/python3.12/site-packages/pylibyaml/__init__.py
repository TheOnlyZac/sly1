""" Speed up PyYAML by using LibYAML bindings by default """

__version__ = '0.1.0'

__all__ = ['monkey_patch_pyyaml', 'restore_original_pyyaml']

import importlib
import inspect
import sys
import warnings

# We want to insert somewhere around here. Luckily this code hasn't changed in a long time.
# https://github.com/yaml/pyyaml/blob/538b5c93f7d5dee40322893c1e524e94a4f8bbde/lib3/yaml/__init__.py#L17
insert_after = """
except ImportError:
    __with_libyaml__ = False
"""

# Insertions will be similar to the following, but may vary slightly based on PyYAML version.
# BaseLoader = CBaseLoader
# SafeLoader = CSafeLoader
# FullLoader = CFullLoader
# UnsafeLoader = CUnsafeLoader
# Loader = CLoader
# BaseDumper = CBaseDumper
# SafeDumper = CSafeDumper
# Dumper = CDumper
insertions = None

# Several functions explicitly reference loader.Loader, just as a way of avoiding conflicts with formal function
# arguments. They really just need to refer to the module-level names.
# add_implicit_resolver
# https://github.com/yaml/pyyaml/blob/5.3.1/lib3/yaml/__init__.py#L317-L319
# add_path_resolver
# https://github.com/yaml/pyyaml/blob/5.3.1/lib3/yaml/__init__.py#L332-L334
# add_constructor
# https://github.com/yaml/pyyaml/blob/5.3.1/lib3/yaml/__init__.py#L346-L348
# add_multi_constructor
# https://github.com/yaml/pyyaml/blob/5.3.1/lib3/yaml/__init__.py#L360-L362
replacements = {
    "loader.Loader": "globals().Loader",
    "loader.FullLoader": "globals().FullLoader",
    "loader.UnsafeLoader": "globals().UnsafeLoader",
}

original_pyyaml_init_py = None
modified_pyyaml_init_py = None

def monkey_patch_pyyaml(force=False):
    """
    Monkey patch the pyyaml library, allowing it to use libyaml bindings
    (CDumpers and CLoaders) by default if they are available.
    Executes automatically on module import, if called before 'import yaml'.
    Otherwise, needs to run with 'force=True'.
    """
    global insert_after
    global insertions
    global original_pyyaml_init_py
    global modified_pyyaml_init_py

    if 'yaml' in sys.modules and not force:
        warnings.warn("PyYAML already loaded, refusing to patch.", ImportWarning)
        return

    try:
        import yaml
    except ImportError:
        warnings.warn("PyYAML not found, nothing to do.", ImportWarning)
        return

    if not yaml.__with_libyaml__:
        warnings.warn("LibYAML not available, nothing to do.", ImportWarning)
        return

    # Read the contents of PyYAML's __init__.py
    try:
        s = inspect.getsource(yaml)
    except:
        warnings.warn("Unable to get original source code for pyyaml __init__.py", ImportWarning)
        return
    else:
        original_pyyaml_init_py = s

    # Find the insertion point
    pos = s.find(insert_after) + len(insert_after)
    if pos == -1:
        warnings.warn("Insertion point in __init__.py not found.", ImportWarning)
        return

    # Dynamically build the list of insertions
    insertions = "\n" + "".join(["{} = {}\n".format(c[1:], c) for c in yaml.cyaml.__all__])
    s = s[:pos] + insertions + s[pos:]
    for old, new in replacements.items():
        s = s.replace(old, new)

    # Reload the modified code to update the function and class definitions
    try:
        exec(s, yaml.__dict__)
    except:
        warnings.warn("Monkey patching PyYAML failed.", ImportWarning)
    else:
        modified_pyyaml_init_py = s


def restore_original_pyyaml():
    """
    Re-import the unmodified pyyaml library.
    """
    import yaml
    importlib.reload(yaml)


monkey_patch_pyyaml()

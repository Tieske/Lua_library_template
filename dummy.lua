-- workaround file, because 'datafile' needs to be called from a module, not a commandline script
local datafile = require("datafile")

local unpack   = unpack or table.unpack
local pack     = table.pack or function(...) return { n = select('#', ...), ... } end

return {
  open = function(...)
    -- datafile needs a stack entry, so cannot use a tailcall here, hence pack/unpack
    local result = pack(datafile.open(...))
    return unpack(result)
  end
}

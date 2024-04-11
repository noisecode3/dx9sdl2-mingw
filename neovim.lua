-- Add this to you're workflow
-- install lspconfig plugin
-- install clangd lsp server with Mason or whatever
local nvim_lsp = require('lspconfig')
nvim_lsp.clangd.setup{}
vim.g.current_shiftwidth = 4

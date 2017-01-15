" Vim syntax file
" Language:	Sipp
" Current Maintainer:	Lars Sydnes
" Last Change: Mars 2016

if exists("b:current_syntax")
  finish
endif

" Read the C syntax to start with
if version < 600
  so <sfile>:p:h/c.vim
else
  runtime! syntax/c.vim
  unlet b:current_syntax
endif

syn keyword sppStatement	si les gjenta hvis ellers metode slutt svar repter bryt lagre hent kurve punkter liste tabell splitt vend sorter baklengs lagBlokk leggTil hode hale tallMellom trekkUt utvalg lesInnTall ja nei og eller ikke
syn keyword sppType		Tall Tekst Liste TallListe Ordliste Tabell Klokke Par Parliste Trio TrioListe Magisk Metode


" Default highlighting
if version >= 508 || !exists("did_cpp_syntax_inits")
  if version < 508
    let did_cpp_syntax_inits = 1
    command -nargs=+ HiLink hi link <args>
  else
    command -nargs=+ HiLink hi def link <args>
  endif
  HiLink sppStatement		Statement
  HiLink sppType		Type
  delcommand HiLink
endif

let b:current_syntax = "cpp"

" vim: ts=8

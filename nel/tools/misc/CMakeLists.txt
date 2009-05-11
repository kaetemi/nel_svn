SUBDIRS(bnp_make disp_sheet_id make_sheet_id xml_packer)

IF(QT4_FOUND)
  ADD_SUBDIRECTORY(words_dic_qt)
  ADD_SUBDIRECTORY(message_box_qt)
ENDIF(QT4_FOUND)


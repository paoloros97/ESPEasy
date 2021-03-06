
void addButton(const String& url, const String& label) {
  addButton(url, label, "");
}

void addButton(const String& url, const String& label, const String& classes) {
  addButton(url, label, classes, true);
}

void addButton(const String& url, const String& label, const String& classes, bool enabled)
{
  html_add_button_prefix(classes, enabled);
  String html;
  html.reserve(8 + url.length() + label.length());
  html += url;
  html += "'>";
  html += label;
  html += F("</a>");
  addHtml(html);
}

void addButtonWithSvg(const String& url, const String& label)
{
  addButtonWithSvg(url, label, "", false);
}

void addButtonWithSvg(const String& url, const String& label, const String& svgPath, bool needConfirm) {
  addHtml(F("<a class='button link' href='"));
  addHtml(url);
  #ifndef BUILD_MINIMAL_OTA
  bool hasSVG = svgPath.length() > 0;
  if (hasSVG) 
  {
    String altText;
    altText.reserve(7 + label.length());
    altText = F("' alt='");
    altText += label;
    addHtml(altText);
  }
  #endif 

  if (needConfirm) {
    addHtml(F("' onclick='return confirm(\"Are you sure?\")"));
  }
  addHtml(F("'>"));

  #ifndef BUILD_MINIMAL_OTA
  if (hasSVG) {
    addHtml(F("<svg width='24' height='24' viewBox='-1 -1 26 26' style='position: relative; top: 5px;'>"));
    addHtml(svgPath);
    addHtml(F("</svg>"));
  } else 
  #endif
  {
    addHtml(label);
  }
  addHtml(F("</a>"));
}

void addSaveButton(const String& url, const String& label)
{
#ifdef BUILD_MINIMAL_OTA
  addButtonWithSvg(url, label
                   , ""
                   , false);
#else // ifdef BUILD_MINIMAL_OTA
  addButtonWithSvg(url,
                   label
                   ,
                   F(
                     "<path d='M19 12v7H5v-7H3v7c0 1.1.9 2 2 2h14c1.1 0 2-.9 2-2v-7h-2zm-6 .67l2.59-2.58L17 11.5l-5 5-5-5 1.41-1.41L11 12.67V3h2v9.67z'  stroke='white' fill='white' ></path>")
                   ,
                   false);
#endif // ifdef BUILD_MINIMAL_OTA
}

void addDeleteButton(const String& url, const String& label)
{
#ifdef BUILD_MINIMAL_OTA
  addButtonWithSvg(url, label
                   , ""
                   , true);
#else // ifdef BUILD_MINIMAL_OTA
  addButtonWithSvg(url,
                   label
                   ,
                   F(
                     "<path fill='none' d='M0 0h24v24H0V0z'></path><path d='M6 19c0 1.1.9 2 2 2h8c1.1 0 2-.9 2-2V7H6v12zM8 9h8v10H8V9zm7.5-5l-1-1h-5l-1 1H5v2h14V4h-3.5z' stroke='white' fill='white' ></path>")
                   ,
                   true);
#endif // ifdef BUILD_MINIMAL_OTA
}

void addWideButton(const String& url, const String& label) {
  addWideButton(url, label, "", true);
}

void addWideButton(const String& url, const String& label, const String& classes) {
  addWideButton(url, label, classes, true);
}

void addWideButton(const String& url, const String& label, const String& classes, bool enabled)
{
  html_add_wide_button_prefix(classes, enabled);
  String html;
  html.reserve(8 + url.length() + label.length());
  html += url;
  html += "'>";
  html += label;
  html += F("</a>");
  addHtml(html);
}

void addSubmitButton()
{
  addSubmitButton(F("Submit"), "");
}

// add submit button with different label and name
void addSubmitButton(const String& value, const String& name) {
  addSubmitButton(value, name, "");
}

void addSubmitButton(const String& value, const String& name, const String& classes)
{
  addHtml(F("<input class='button link"));

  if (classes.length() > 0) {
    addHtml(" ");
    addHtml(classes);
  }
  addHtml(F("' type='submit' value='"));
  addHtml(value);

  if (name.length() > 0) {
    addHtml(F("' name='"));
    addHtml(name);
  }
  addHtml(F("' onclick='toasting()'/><div id='toastmessage'></div>"));
}

// add copy to clipboard button
void addCopyButton(const String& value, const String& delimiter, const String& name)
{
  TXBuffer += jsClipboardCopyPart1;
  addHtml(value);
  TXBuffer += jsClipboardCopyPart2;
  addHtml(delimiter);
  TXBuffer += jsClipboardCopyPart3;

  // Fix HTML
  addHtml(F("<button class='button link' onclick='setClipboard()'>"));
  addHtml(name);
  addHtml(" (");
  html_copyText_marker();
  addHtml(F(")</button>"));
}

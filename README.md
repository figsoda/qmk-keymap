```bash
qmk setup
cd ~/qmk_firmware
git clone https://github.com/figsoda/qmk-keymap keyboards/keebio/iris/keymaps/figsoda
sudo qmk flash -kb keebio/iris/rev6 -km figsoda
```

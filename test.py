import clib

for _ in range(10**6):
  try:
    clib.error_with_payload()
  except Exception:
    pass
